/*
    This file is part of GILES.

    GILES is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GILES is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with GILES.  If not, see <http://www.gnu.org/licenses/>.
*/

/*!
    @file Coefficients.hpp
    @brief Contains the internal representation of the Coefficients file.
    @author Scott Egerton
    @date 2017-2019
    @copyright GNU Affero General Public License Version 3+
*/

#include <algorithm>  // for find
#include <stdexcept>  // for out_of_range

#include "Coefficients.hpp"

namespace GILES
{
namespace Internal
{
//! @brief Retrieves the category that the given instruction is contained
//! within. This is a utility function that is used to assist in retrieving
//! other
//! data from the coefficients.
//! @param p_opcode The opcode of the instruction for which the category will
//! be retrieved.
//! @returns The name of the category that the instruction is contained within.
//! If the coefficients are not categorised then the instruction opcode is
//! returned.
//! @exception std::out_of_range This exception is thrown if the instruction
//! given by p_opcode is not found within any category in the coefficients.
//! @see https://eprint.iacr.org/2016/517 Section 4.2 for more on the
//! categories.
const std::string& GILES::Internal::Coefficients::Get_Instruction_Category(
    const std::string& p_opcode) const
{
    for (const auto& category : m_coefficients.items())
    {
        // The Instruction Categories are optional. If there are no
        // categories then the 'category' is simply the opcode
        if (category.key() == p_opcode)
        {
            return p_opcode;
        }

        // Ensure this category has an instruction section before accessing it.
        if (category.value().find("Instructions") != category.value().end())
        {
            // If the instruction is in this category, return the name of the
            // category.
            if (const auto& instructions = category.value().at("Instructions");
                instructions.end() !=
                std::find(instructions.begin(), instructions.end(), p_opcode))
            {
                return category.key();
            }
        }
    }
    throw std::out_of_range("This instruction (" + p_opcode +
                            ") was not found within the Coefficients");
}

//! @brief Retrieves a list of all interaction terms contained within the
//! coefficients. This is needed in order to ensure the Model will be
//! provided with the terms it requires. The interaction terms of the first
//! coefficient are used as they should be identical to all other
//! coefficients.
//! @returns All interaction terms contained, as an unordered set. An
//! unordered set is used as the json standard dictates that json data is
//! unordered therefore we should not expect any particular order.
const std::unordered_set<std::string>
GILES::Internal::Coefficients::Get_Interaction_Terms() const
{
    // Coefficients are optional, this handles that case.
    if (m_coefficients.empty())
    {
        return {};
    }
    std::unordered_set<std::string> interaction_terms;
    for (const auto& interaction_term :
         m_coefficients.front()["Coefficients"].items())
    {
        interaction_terms.insert(interaction_term.key());
    }
    return interaction_terms;
}

//! @brief Retrieves the coefficients for the interaction term given by
//! p_interaction_term under the instruction category that contains the
//! instruction given by p_opcode.
//! @param p_opcode  The opcode of the instruction that the Coefficients are
//! required for.
//! @param p_interaction_term The interaction term from within the model
//! that the Coefficients are required for.
//! @returns An ordered vector of the coefficient values.
const std::vector<double> GILES::Internal::Coefficients::Get_Coefficients(
    const std::string& p_opcode, const std::string& p_interaction_term) const
{
    return get_coefficient<std::vector<double>>(p_opcode, p_interaction_term);
}

//! @brief Retrieves the Constant for the Instruction Category that contains
//! the instruction provided by p_opcode.
//! @param p_opcode The opcode of the instruction that the Constant is
//! required for.
//! @returns The value of the constant for the category that the
//! instruction belongs to.
double
GILES::Internal::Coefficients::Get_Constant(const std::string& p_opcode) const
{
    return get_value_opcode<double>(p_opcode, "Constant");
}
}  // namespace Internal
}  // namespace GILES
