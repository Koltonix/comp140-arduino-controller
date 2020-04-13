using comp140.data;

namespace comp140.interfaces
{
    public interface ILane
    {
        Lane GetLane(int index);
        Lane[] GetAllLanes();
    }
}