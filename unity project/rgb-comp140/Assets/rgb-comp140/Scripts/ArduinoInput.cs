//////////////////////////////////////////////////
// Christopher Robertson 2020.
// https://github.com/Koltonix
// MIT License Copyright (c) 2020
//////////////////////////////////////////////////
using System;
using System.IO.Ports;
using UnityEngine;

using comp140.data;

namespace comp140.input
{
    public class ArduinoInput : MonoBehaviour
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
    }

}