// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file Entity.hpp
 *
 */

#ifndef _FASTDDS_ENTITY_HPP_
#define _FASTDDS_ENTITY_HPP_

#include <dds/core/status/Status.hpp>
#include <fastdds/dds/core/conditions/StatusCondition.hpp>
#include <fastdds/rtps/common/InstanceHandle.h>
#include <fastrtps/types/TypesBase.h>

namespace eprosima {
namespace fastdds {
namespace dds {

/**
 * @brief The Entity class is the abstract base class for all the objects that support QoS policies, a listener and
 * a status condition.
 *
 */
class Entity
{
public:

    RTPS_DllAPI Entity(
            const ::dds::core::status::StatusMask& mask = ::dds::core::status::StatusMask::all())
        : status_condition_(this)
        , enable_(false)
    {
        status_condition_.set_enabled_statuses(mask);
    }

    /**
     * @brief enable This operation enables the Entity
     * @return true
     */
    RTPS_DllAPI virtual fastrtps::types::ReturnCode_t enable()
    {
        enable_ = true;
        return fastrtps::types::ReturnCode_t::RETCODE_OK;
    }

    RTPS_DllAPI void close()
    {
        enable_ = false;
    }

    /**
     * @brief get_statuscondition Retrieves the StatusCondition associated to the Entity
     * @return Pointer to the StatusCondition
     */
    RTPS_DllAPI StatusCondition* get_statuscondition()
    {
        return &status_condition_;
    }

    /**
     * @brief get_status_mask Retrieves the set of relevant statuses for the Entity
     * @return Reference to the StatusMask with the relevant statuses set to 1
     */
    RTPS_DllAPI const ::dds::core::status::StatusMask& get_status_mask() const
    {
        return status_condition_.get_enabled_statuses();
    }

    /**
     * @brief get_status_changes Retrieves the set of statuses that has been triggered since the last time
     * the application read it
     * @return Reference to a StatusMask with the triggered status set to 1
     */
    RTPS_DllAPI const ::dds::core::status::StatusMask& get_status_changes() const
    {
        return status_condition_.get_triggered_status();
    }

    /**
     * @brief get_instance_handle Retrieves the instance handler that represents the Entity
     * @return Reference to the InstanceHandle
     */
    RTPS_DllAPI const fastrtps::rtps::InstanceHandle_t& get_instance_handle() const
    {
        return instance_handle_;
    }

    /**
     * @brief is_enabled Checks if the Entity is enabled
     * @return true if enabled, false if not
     */
    RTPS_DllAPI bool is_enabled() const
    {
        if (enable_)
        {
            return true;
        }
        return false;
    }

    RTPS_DllAPI bool operator ==(
            const Entity& other) const
    {
        return (this->instance_handle_ == other.instance_handle_);
    }

protected:

    RTPS_DllAPI void set_instance_handle(
            const fastrtps::rtps::InstanceHandle_t& handle)
    {
        instance_handle_ = handle;
    }

    StatusCondition status_condition_;

    fastrtps::rtps::InstanceHandle_t instance_handle_;

    bool enable_;

};


/**
 * @brief The DomainEntity class Subclass of Entity created in order to differentiate between DomainParticipants
 * and the rest of Entities
 */
class DomainEntity : public Entity
{
public:

    RTPS_DllAPI DomainEntity(
            const ::dds::core::status::StatusMask& mask = ::dds::core::status::StatusMask::all())
        : Entity(mask)
    {
    }

};

} // namespace dds
} // namespace fastdds
} // namespace eprosima

#endif // _FASTDDS_ENTITY_HPP_
