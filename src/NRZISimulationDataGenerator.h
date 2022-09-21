#ifndef NRZI_SIMULATION_DATA_GENERATOR
#define NRZI_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class NRZIAnalyzerSettings;

class NRZISimulationDataGenerator
{
public:
	NRZISimulationDataGenerator();
	~NRZISimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, NRZIAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	NRZIAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //NRZI_SIMULATION_DATA_GENERATOR
