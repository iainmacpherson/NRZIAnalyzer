#ifndef NRZI_ANALYZER_H
#define NRZI_ANALYZER_H

#include <Analyzer.h>
#include "NRZIAnalyzerResults.h"
#include "NRZISimulationDataGenerator.h"

class NRZIAnalyzerSettings;
class ANALYZER_EXPORT NRZIAnalyzer : public Analyzer2
{
public:
	NRZIAnalyzer();
	virtual ~NRZIAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< NRZIAnalyzerSettings > mSettings;
	std::auto_ptr< NRZIAnalyzerResults > mResults;
	AnalyzerChannelData* mDataSerial;
	AnalyzerChannelData* mClkSerial;

	NRZISimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //NRZI_ANALYZER_H
