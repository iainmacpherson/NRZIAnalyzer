#include "NRZIAnalyzer.h"
#include "NRZIAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

NRZIAnalyzer::NRZIAnalyzer()
: Analyzer2(),
  mSettings( new NRZIAnalyzerSettings() ),
  mSimulationInitilized( false )
{
  SetAnalyzerSettings( mSettings.get() );
}

NRZIAnalyzer::~NRZIAnalyzer()
{
  KillThread();
}

void NRZIAnalyzer::SetupResults()
{
  mResults.reset( new NRZIAnalyzerResults( this, mSettings.get() ) );
  SetAnalyzerResults( mResults.get() );
  mResults->AddChannelBubblesWillAppearOn( mSettings->mInputChannel );
}

void NRZIAnalyzer::WorkerThread()
{
  mSampleRateHz = GetSampleRate();

  mDataSerial = GetAnalyzerChannelData( mSettings->mInputChannel );
  mClkSerial = GetAnalyzerChannelData( mSettings->mClkChannel );

  // Jump immediately to the start of the clock
  // NOTE: this is not robust but for my use case this is always less than 32 bits worth of samples.
  U32 samples_to_advance = (U32) (mClkSerial->GetSampleOfNextEdge() - mClkSerial->GetSampleNumber());
  mClkSerial->Advance( samples_to_advance );
  mDataSerial->Advance( samples_to_advance );

  U8 last_bit_level = 0;

  for( ; ; )
  {
    U8 data = 0;
    U8 mask = 1 << 7;

    U64 starting_sample = mDataSerial->GetSampleNumber();

    for( U32 i=0; i<8; i++ )
    {
      //let's put a dot exactly where we sample this bit:
      mResults->AddMarker( mDataSerial->GetSampleNumber(), AnalyzerResults::Dot, mSettings->mInputChannel );

      U8 current_bit_level = (mDataSerial->GetBitState() == BIT_HIGH) ? 1 : 0;

      // decode the NRZI
      if( last_bit_level ^ current_bit_level )
        data |= mask;

      last_bit_level = current_bit_level;

      mask = mask >> 1;

      // advance together after the next edge of the clock
      samples_to_advance = (U32) (mClkSerial->GetSampleOfNextEdge() - mClkSerial->GetSampleNumber());
      mClkSerial->Advance( samples_to_advance );
      mDataSerial->Advance( samples_to_advance );
    }

    //we have a byte to save.
    Frame frame;
    frame.mData1 = data;
    frame.mFlags = 0;
    frame.mStartingSampleInclusive = starting_sample;
    frame.mEndingSampleInclusive = mDataSerial->GetSampleNumber();

    mResults->AddFrame( frame );
    mResults->CommitResults();
    ReportProgress( frame.mEndingSampleInclusive );
  }
}

bool NRZIAnalyzer::NeedsRerun()
{
  return false;
}

U32 NRZIAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
  if( mSimulationInitilized == false )
  {
    mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
    mSimulationInitilized = true;
  }

  return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 NRZIAnalyzer::GetMinimumSampleRateHz()
{
  return mSettings->mClkHz*2;  // nyquest at a minimum
}

const char* NRZIAnalyzer::GetAnalyzerName() const
{
  return "Bare Bones NRZI Analyzer";
}

const char* GetAnalyzerName()
{
  return "Bare Bones NRZI Analyzer";
}

Analyzer* CreateAnalyzer()
{
  return new NRZIAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
  delete analyzer;
}
