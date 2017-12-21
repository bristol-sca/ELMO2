/*
    This file is part of ELMO-2.

    ELMO-2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    ELMO-2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ELMO-2.  If not, see <http://www.gnu.org/licenses/>.
*/

/*!
    @file Register.hpp
    @brief The internal representation of an individual register.
    @author Scott Egerton
    @date 2017
    @copyright GNU General Public License Version 2+
*/

#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <string>

namespace ELMO2
{
//! @class Register
//! @brief The internal representation of an individual register.
//! This contains the opcode and operands of the instruction as well as a list
//! of registers that have been changed making use of the Register class.
//! TODO:
//! ***************************************************************************************
//! @see https://en.wikipedia.org/wiki/Processor_register
//! TODO: Maybe this sin't a good way to store registers as it makes it
//! difficult store in a data structure such as a map. Actually maybe a map
//! would be great?
class Register
{
private:
    //! The name of the register.
    const std::string m_name;

    //! The value conatined within that register. TODO: Change this type?
    const std::string m_value;

public:
    //! @brief The constructor should take all details of the register which
    //! cannot be changed once set as this is meant to be a representation of a
    //! register, not a smart class with lots of functionality.
    //! @param p_name The name of the register.
    //! @param p_value The value conatined within that register.
    Register(const std::string& p_name, const std::string& p_value)
        : m_name(p_name), m_value(p_value)
    {
    }

    //! @brief Retrives the name of the register.
    //! @returns The name of the register.
    const std::string& get_name() const { return m_name; }

    //!@brief Retives the value conatined within that register.
    const std::string& get_value() const { return m_value; }
};
} // namespace ELMO2

#endif