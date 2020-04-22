using System;
using System.Collections;
using System.IO.Ports;
using UnityEngine;

using comp140.data;
using comp140.interfaces;

namespace comp140.input
{
    public class ArduinoInput : MonoBehaviour, ILane
    {
        [Header("Arduino Settings")]
        [SerializeField]
        private int commPort;
        [SerializeField]
        private int readTimeout = 50;
        private SerialPort serial = null;
        private Coroutine refreshCoroutine;

        [Header("Input Settings")]
        private const int numOfLanes = 1;
        private Lane[] lanes = new Lane[numOfLanes];

        private void Start()
        {
            ConnectToSerial();
            
            for (int i = 0; i < numOfLanes; i++)
            {
                lanes[i] = new Lane(i);
            }

            refreshCoroutine = StartCoroutine(GetArduinoInput(0.5f));
        }

        private void Update()
        {
            if (refreshCoroutine == null) StartCoroutine(GetArduinoInput(0.5f));
        }

        private void ConnectToSerial()
        {
            serial = new SerialPort("\\\\.\\COM" + commPort, 115200);
            serial.ReadTimeout = readTimeout;
            serial.Open();
            serial.BaseStream.Flush();
        }

        private IEnumerator GetArduinoInput(float interval)
        {
            //lanes[0].encoderValue = Convert.ToInt32(GetEncoderInputFromArduino("a"));
            //lanes[0].encoderValue = Convert.ToInt32(GetEncoderInputFromArduino("b"));
            //lanes[0].timeLeft = float.Parse(GetEncoderInputFromArduino("c"));
            
            string selectedColour = GetEncoderInputFromArduino("d");
            if (selectedColour != null) lanes[0].selectedColour = ColourConverter.DecodeColourString(selectedColour);
            yield return new WaitForSeconds(interval);

            string firstColour = GetEncoderInputFromArduino("e");
            if (firstColour != null) lanes[0].colourOrder[0] = ColourConverter.DecodeColourString(firstColour);
            yield return new WaitForSeconds(interval);

            string secondColour = GetEncoderInputFromArduino("f");
            if (secondColour != null) lanes[0].colourOrder[1] = ColourConverter.DecodeColourString(secondColour);
            yield return new WaitForSeconds(interval);

            string thirdColour = GetEncoderInputFromArduino("g");
            if (thirdColour != null) lanes[0].colourOrder[2] = ColourConverter.DecodeColourString(thirdColour);

            refreshCoroutine = null;
            yield return null;
        }

        private string GetEncoderInputFromArduino(string identifier)
        {
            WriteToArduino(identifier);
            String value = ReadFromArduino(readTimeout);

            if (value != null)
            {
                return value;
            }

            return null;
        }

        private void WriteToArduino(string message)
        {
            serial.WriteLine(message);
            serial.BaseStream.Flush();
        }
            
        private string ReadFromArduino(int timeout)
        {
            serial.ReadTimeout = timeout;
            try
            {
                return serial.ReadLine();
            }
            catch 
            {
                return null;
            }
        }

        private void OnDestroy()
        {
            serial.Close();
        }

        #region ILane Interface Implementation
        public Lane GetLane(int index)
        {
            return lanes[index];
        }

        public Lane[] GetAllLanes()
        {
            return lanes;
        }
        #endregion
    }

}