// Constraints:

// -10^5 <= num <= 10^5
// There will be at least one element in the data structure before calling findMedian.
// At most 5 * 104 calls will be made to addNum and findMedian.

// Follow up:

// If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
// If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?

#include <queue>
#include <iostream>

const static auto fast = []
{ 
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    //std::cout.tie(nullptr);
    return 0;
}();

class MedianFinder
{
private:
    std::priority_queue<int> maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    /**
     * @brief Rebalances the maxHeap and minHeap to maintain the size property.
     * 
     * @details
     * The invariant maintained is that the size of maxHeap is either equal to the size of minHeap or
     * greater by one. This ensures efficient median finding, where if both heaps are of equal size,
     * the median is the average of the tops of both heaps. If maxHeap has one more element, the median
     * is the top of maxHeap.
     */
    void rebalanceHeaps()
    {
        if (maxHeap.size() > minHeap.size() + 1)
        {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (minHeap.size() > maxHeap.size())
        {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

public:
    /**
     * @brief Constructor for the MedianFinder class.
     */
    MedianFinder() = default;

    /**
     * @brief Adds a number into the data structure.
     * 
     * @details
     * If the new number is smaller than the maximum of the lower half, it gets added to the max heap,
     * otherwise, it is added to the min heap. After adding, it calls rebalanceHeaps to
     * ensure the size difference between the two heaps is no more than one.
     * 
     * @param num The number to be added.
     */
    void addNum(int num)
    {
        if (maxHeap.empty() || num <= maxHeap.top())
        {
            maxHeap.push(num);
        }
        else
        {
            minHeap.push(num);
        }

        rebalanceHeaps();
    }

    /**
     * @brief Finds the median of all numbers added so far.
     * 
     * @details
     * If one heap is larger, the median is the top of that heap. If both heaps are the same size,
     * the median is the average of the tops of both heaps.
     * 
     * @return The median of the numbers.
     */
    double findMedian()
    {
        if (maxHeap.size() > minHeap.size())
        {
            return maxHeap.top();
        }
        else if (minHeap.size() > maxHeap.size())
        {
            return minHeap.top();
        }
        else
        {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */