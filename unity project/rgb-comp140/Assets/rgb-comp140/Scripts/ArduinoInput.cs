//////////////////////////////////////////////////
// Christopher Robertson 2020.
// https://github.com/Koltonix
// MIT License Copyright (c) 2020
//////////////////////////////////////////////////
using System;
using System.IO.Ports;
using UnityEngine;
using COMP140.Data;

namespace COMP140.Input
{
    /// <summary>
    /// Handles the Input from the Arduino using a Serial Communicator.
    /// Assigns these values to the lanes.
    /// </summary>
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

            //Checking the fourth element to see which lane it is
            if (laneValues != null && laneValues[3] == '0')
            {
                lanes[0].allValues = laneValues.DecodeArduinoString();
                lanes[0].AssignStringsToValues(lanes[0].allValues);
            }

            //Checking the fourth element to see which lane it is
            else if (laneValues != null && laneValues[3] == '1')
            {
                lanes[1].allValues = laneValues.DecodeArduinoString();
                lanes[1].AssignStringsToValues(lanes[1].allValues);
            }
        }

        /// <summary>Serial Communicator Initialisation.</summary>
        private void ConnectToSerial()
        {
            serial = new SerialPort("\\\\.\\COM" + commPort, 9600);
            serial.ReadTimeout = readTimeout;
            serial.Open();
            serial.BaseStream.Flush();
        }
        
        /// <summary>Reads whatever the Arduino has printed to the Serial lane.</summary>
        /// <param name="timeout">Time until it stops reading.</param>
        /// <returns>The string transferred from the Arduino.</returns>
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