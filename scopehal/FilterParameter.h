/***********************************************************************************************************************
*                                                                                                                      *
* ANTIKERNEL v0.1                                                                                                      *
*                                                                                                                      *
* Copyright (c) 2012-2020 Andrew D. Zonenberg                                                                          *
* All rights reserved.                                                                                                 *
*                                                                                                                      *
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the     *
* following conditions are met:                                                                                        *
*                                                                                                                      *
*    * Redistributions of source code must retain the above copyright notice, this list of conditions, and the         *
*      following disclaimer.                                                                                           *
*                                                                                                                      *
*    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the       *
*      following disclaimer in the documentation and/or other materials provided with the distribution.                *
*                                                                                                                      *
*    * Neither the name of the author nor the names of any contributors may be used to endorse or promote products     *
*      derived from this software without specific prior written permission.                                           *
*                                                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE AUTHORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   *
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL *
* THE AUTHORS BE HELD LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES        *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR       *
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                                                                          *
*                                                                                                                      *
***********************************************************************************************************************/

/**
	@file
	@author Andrew D. Zonenberg
	@brief Declaration of FilterParameter
 */

#ifndef FilterParameter_h
#define FilterParameter_h

class FilterParameter
{
public:
	enum ParameterTypes
	{
		TYPE_FLOAT,
		TYPE_INT,
		TYPE_BOOL,
		TYPE_FILENAME,	//one file
		TYPE_FILENAMES,	//multiple files
		TYPE_ENUM,		//enumerated constant
		TYPE_STRING		//arbitrary string
	};

	FilterParameter(ParameterTypes type = FilterParameter::TYPE_FLOAT, Unit unit  = Unit(Unit::UNIT_FS));

	void ParseString(const std::string& str);
	std::string ToString();

	bool GetBoolVal()
	{ return (m_intval != 0); }

	int64_t GetIntVal();
	float GetFloatVal();
	std::string GetFileName();
	std::vector<std::string> GetFileNames();

	void SetBoolVal(bool b)
	{ m_intval = b; }
	void SetIntVal(int64_t i);
	void SetFloatVal(float f);
	void SetFileName(const std::string& f);
	void SetFileNames(const std::vector<std::string>& names);

	ParameterTypes GetType()
	{ return m_type; }

	//File filters for TYPE_FILENAME / TYPE_FILENAMES(otherwise ignored)
	std::string m_fileFilterMask;
	std::string m_fileFilterName;

	//Specifies TYPE_FILENAME is an output
	bool m_fileIsOutput;

	//Add an enumerated value
	void AddEnumValue(const std::string& name, int value)
	{
		m_forwardEnumMap[name] = value;
		m_reverseEnumMap[value] = name;
	}

	//Gets a list of legal values
	void GetEnumValues(std::vector<std::string>& values)
	{
		for(auto it : m_forwardEnumMap)
			values.push_back(it.first);
	}

protected:
	ParameterTypes m_type;

	Unit						m_unit;

	std::map<std::string, int>	m_forwardEnumMap;
	std::map<int, std::string>	m_reverseEnumMap;

	int64_t						m_intval;
	float						m_floatval;
	std::string					m_string;
	std::vector<std::string>	m_filenames;
};

#endif
