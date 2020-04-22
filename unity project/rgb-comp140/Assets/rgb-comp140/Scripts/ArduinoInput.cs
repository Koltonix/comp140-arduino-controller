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

        [Header("Input Settings")]
        public Lane[] lanes;

        private void Start()
        {
            ConnectToSerial();
        }

        private void Update()
        {
            string laneValues = ReadFromArduino(readTimeout);

            if (laneValues != null && laneValues[3] == '0')
            {
                lanes[0].allValues = laneValues.DecodeArduinoString();
                lanes[0].AssignStringsToValues(lanes[0].allValues);
            }

            else if (laneValues != null && laneValues[3] == '1')
            {
                lanes[1].allValues = laneValues.DecodeArduinoString();
                lanes[1].AssignStringsToValues(lanes[1].allValues);
            }
        }

        private void ConnectToSerial()
        {
            serial = new SerialPort("\\\\.\\COM" + commPort, 9600);
            serial.ReadTimeout = readTimeout;
            serial.Open();
            serial.BaseStream.Flush();
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