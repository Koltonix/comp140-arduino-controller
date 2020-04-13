using UnityEngine;

public class GameController : MonoBehaviour
{
    private void Start()
    {
        Debug.Log(ColourConverter.DecodeColourString("255,255,255"));
    }
}
