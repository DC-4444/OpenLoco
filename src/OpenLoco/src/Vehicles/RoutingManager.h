#pragma once

#include "Routing.h"

#include <iterator>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace OpenLoco::Vehicles::RoutingManager
{
    constexpr uint16_t kAllocatedButFreeRoutingStation = 0xFFFEU; // Indicates that this array is allocated to a vehicle but no station has been set.
    constexpr uint16_t kRoutingNull = 0xFFFFU;                    // Indicates that this array is unallocated to any vehicle.

    std::optional<RoutingHandle> getAndAllocateFreeRoutingHandle();
    void freeRoutingHandle(const RoutingHandle handle);
    uint16_t getRouting(const RoutingHandle handle);
    void setRouting(const RoutingHandle handle, uint16_t routing);
    void freeRouting(const RoutingHandle handle);
    bool isEmptyRoutingSlotAvailable();
    void resetRoutingTable();

    struct RingView
    {
    private:
        struct Iterator
        {
            enum class Direction : bool
            {
                forward,
                reverse,
            };

        private:
            RoutingHandle _current;
            bool _hasLooped = false;
            bool _isEnd = false;
            Direction _direction = Direction::forward;

        public:
            Iterator(const RoutingHandle& begin, bool isEnd, Direction direction);

            Iterator& operator++();
            Iterator operator++(int)
            {
                Iterator res = *this;
                ++(*this);
                return res;
            }

            Iterator& operator--();
            Iterator operator--(int)
            {
                Iterator res = *this;
                --(*this);
                return res;
            }

            bool operator==(const Iterator& other) const;

            RoutingHandle& operator*()
            {
                return _current;
            }

            const RoutingHandle& operator*() const
            {
                return _current;
            }

            RoutingHandle& operator->()
            {
                return _current;
            }

            const RoutingHandle& operator->() const
            {
                return _current;
            }

            // iterator traits
            using difference_type = std::ptrdiff_t;
            using value_type = RoutingHandle;
            using pointer = const RoutingHandle*;
            using reference = const RoutingHandle&;
            using iterator_category = std::bidirectional_iterator_tag;
        };

        RoutingHandle _begin;

    public:
        // currentOrderOffset is relative to beginTableOffset and is where the ring will begin and end
        RingView(const RoutingHandle begin)
            : _begin(begin)
        {
        }

        RingView::Iterator begin() const { return Iterator(_begin, false, Iterator::Direction::forward); }
        RingView::Iterator end() const { return Iterator(_begin, true, Iterator::Direction::forward); }
        auto rbegin() const { return Iterator(_begin, false, Iterator::Direction::reverse); }
        auto rend() const { return Iterator(_begin, true, Iterator::Direction::reverse); }
    };
}
