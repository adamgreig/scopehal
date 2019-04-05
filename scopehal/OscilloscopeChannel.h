/***********************************************************************************************************************
*                                                                                                                      *
* ANTIKERNEL v0.1                                                                                                      *
*                                                                                                                      *
* Copyright (c) 2012-2019 Andrew D. Zonenberg                                                                          *
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
	@brief Declaration of OscilloscopeChannel
 */

#ifndef OscilloscopeChannel_h
#define OscilloscopeChannel_h

#include "CaptureChannel.h"

class ChannelRenderer;
class Oscilloscope;

/**
	@brief A single channel on the oscilloscope.

	Each time the scope is triggered a new CaptureChannel is created with the new capture's data.
 */
class OscilloscopeChannel
{
public:
	enum ChannelType
	{
		CHANNEL_TYPE_ANALOG,
		CHANNEL_TYPE_DIGITAL,

		//Complex datatype from a protocol decoder
		CHANNEL_TYPE_COMPLEX
	};

	OscilloscopeChannel(
		Oscilloscope* scope,
		std::string hwname,
		OscilloscopeChannel::ChannelType type,
		std::string color,
		int width = 1,
		size_t index = 0,
		bool physical = false);
	virtual ~OscilloscopeChannel();

	///Display color (any valid GDK format)
	std::string m_displaycolor;

	///Display name (user defined, defaults to m_hwname)
	std::string m_displayname;

	//Stuff here is set once at init and can't be changed
	ChannelType GetType();
	std::string GetHwname();

	///Get the channel's data
	CaptureChannelBase* GetData();

	///Set new data, overwriting the old data as appropriate
	void SetData(CaptureChannelBase* pNew);

	virtual ChannelRenderer* CreateRenderer();

	int GetWidth();

	//Display time scale (normally the same for all channels)
	float m_timescale;

	Oscilloscope* GetScope()
	{ return m_scope; }

	size_t GetIndex()
	{ return m_index; }

	//Hardware configuration
public:
	bool IsEnabled();
	void Enable();
	void Disable();

	enum CouplingType
	{
		COUPLE_DC_1M,		//1M ohm, DC coupled
		COUPLE_AC_1M,		//1M ohm, AC coupled
		COUPLE_DC_50,		//50 ohm, DC coupled
		COUPLE_GND,			//tie to ground
		COUPLE_SYNTHETIC	//channel is math or otherwise not a direct voltage measurement
	};

	CouplingType GetCoupling();
	void SetCoupling(CouplingType type);

	double GetAttenuation();
	void SetAttenuation(double atten);

	int GetBandwidthLimit();
	void SetBandwidthLimit(int mhz);

	bool IsPhysicalChannel()
	{ return m_physical; }

	double GetVoltageRange();
	void SetVoltageRange(double range);

protected:

	Oscilloscope* m_scope;

	///Capture data
	CaptureChannelBase* m_data;

	///Channel type
	ChannelType m_type;

	///Hardware name as labeled on the scope
	std::string m_hwname;

	///Bus width (1 to N, only meaningful for digital channels)
	int m_width;

	///Set to true if we're the output of a protocol decoder
	bool m_procedural;

	///Channel index
	size_t m_index;

	///true if this is a real physical input on the scope and not a math or other output
	bool m_physical;
};

#endif