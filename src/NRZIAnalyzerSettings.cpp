#include "NRZIAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


NRZIAnalyzerSettings::NRZIAnalyzerSettings()
: mInputChannel( UNDEFINED_CHANNEL ),
  mClkChannel( UNDEFINED_CHANNEL ),
  mClkHz( 25000000 )
{
  mClkChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
  mClkChannelInterface->SetTitleAndTooltip( "Clock", "Clock - Standard Bare Bones NRZI Analyzer" );
  mClkChannelInterface->SetChannel( mClkChannel);

  mInputChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
  mInputChannelInterface->SetTitleAndTooltip( "Data", "Data - Standard Bare Bones NRZI Analyzer" );
  mInputChannelInterface->SetChannel( mInputChannel );

  mClkHzInterface.reset( new AnalyzerSettingInterfaceInteger() );
  mClkHzInterface->SetTitleAndTooltip( "DDR Frequency (Hz)",  "Specify the max frequency in use." );
  mClkHzInterface->SetMax( 50000000 );
  mClkHzInterface->SetMin( 1 );
  mClkHzInterface->SetInteger( mClkHz );

  AddInterface( mClkChannelInterface.get() );
  AddInterface( mInputChannelInterface.get() );
  AddInterface( mClkHzInterface.get() );

  AddExportOption( 0, "Export as text/csv file" );
  AddExportExtension( 0, "text", "txt" );
  AddExportExtension( 0, "csv", "csv" );

  ClearChannels();
  AddChannel( mInputChannel, "Data", false );
  AddChannel( mClkChannel, "Clock", false );
}

NRZIAnalyzerSettings::~NRZIAnalyzerSettings()
{
}

bool NRZIAnalyzerSettings::SetSettingsFromInterfaces()
{
  mInputChannel = mInputChannelInterface->GetChannel();
  mClkChannel = mClkChannelInterface->GetChannel();
  mClkHz = mClkHzInterface->GetInteger();

  ClearChannels();
  AddChannel( mInputChannel, "Data - Bare Bones NRZI Analyzer", true );
  AddChannel( mClkChannel, "Clock - Bare Bones NRZI Analyzer", true );

  return true;
}

void NRZIAnalyzerSettings::UpdateInterfacesFromSettings()
{
  mInputChannelInterface->SetChannel( mInputChannel );
  mClkChannelInterface->SetChannel( mClkChannel );
  mClkHzInterface->SetInteger( mClkHz );
}

void NRZIAnalyzerSettings::LoadSettings( const char* settings )
{
  SimpleArchive text_archive;
  text_archive.SetString( settings );

  text_archive >> mInputChannel;
  text_archive >> mClkChannel;
  text_archive >> mClkHz;

  ClearChannels();
  AddChannel( mInputChannel, "Data - Bare Bones NRZI Analyzer", true );
  AddChannel( mClkChannel, "Clock - Bare Bones NRZI Analyzer", true );

  UpdateInterfacesFromSettings();
}

const char* NRZIAnalyzerSettings::SaveSettings()
{
  SimpleArchive text_archive;

  text_archive << mInputChannel;
  text_archive << mClkChannel;
  text_archive << mClkHz;

  return SetReturnString( text_archive.GetString() );
}
