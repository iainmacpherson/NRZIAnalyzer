#ifndef NRZI_ANALYZER_SETTINGS
#define NRZI_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class NRZIAnalyzerSettings : public AnalyzerSettings
{
public:
	NRZIAnalyzerSettings();
	virtual ~NRZIAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;
  Channel mClkChannel;
  U32 mClkHz;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mClkChannelInterface;
  std::auto_ptr< AnalyzerSettingInterfaceInteger >  mClkHzInterface;
};

#endif //NRZI_ANALYZER_SETTINGS
