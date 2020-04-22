using UnityEngine;
using UnityEngine.UI;
using TMPro;

using comp140.data;
using comp140.interfaces;
using comp140.input;

namespace comp140.gameplay
{
    public class GameController : MonoBehaviour
    {
        [Header("Lane Settings")]
        [SerializeField]
        private GameObject inputObject;
        private ILane laneData;

        [Header("UI Settings")]
        [SerializeField]
        private TextMeshProUGUI[] laneEncoderValue;
        [SerializeField]
        private TextMeshProUGUI[] laneTime;

        [SerializeField]
        private Image[] selectedColours;
        [SerializeField]
        private Image[] queuedColours;

        private void Start()
        {
            if (inputObject) laneData = inputObject.GetComponent<ILane>();
            else if (!inputObject) laneData = FindObjectOfType<ArduinoInput>().GetComponent<ILane>();
        }
    }

}

