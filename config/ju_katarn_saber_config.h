#ifdef CONFIG_TOP
#include "proffieboard_v3_config.h"
#define NUM_BLADES 2
#define NUM_BUTTONS 2
#define VOLUME 400
const unsigned int maxLedsPerStrip = 144;
#define CLASH_THRESHOLD_G 1.0
#define ENABLE_AUDIO
#define ENABLE_MOTION
#define ENABLE_WS2811
#define ENABLE_SD
#define SHARED_POWER_PINS
#define ENABLE_SERIAL
#define IDLE_OFF_TIME 60 * 5 * 1000
#define SAVE_STATE
#define ENABLE_ALL_EDIT_OPTIONS
#endif

#ifdef CONFIG_PRESETS
Preset presets[] = {
  { "Jk1KatarnSmth", "",
    StylePtr<JuBaseStyle<Green>>(),
    StylePtr<Blue>(), "JK1\nKatarn\nSmooth" },
  { "Jk2Katarn", "",
    StyleNormalPtr<AudioFlicker<BLUE, Rgb<0,0,210>>, WHITE, 300, 1000>(),
    StylePtr<Blue>(), "JK2\nKatarn" },
  { "SmthJedi", "tracks/mars.wav",
    StylePtr<Rotoscope<DarkOrange>>(),
    StylePtr<Blue>(), "Style Test" },
  { "Jk1Katarn", "",
    StylePtr<JuBaseStyle2<Yellow>>(),
    StylePtr<Blue>(), "JK1\nKatarn" },
  { "TthCrstl", "tracks/mars.wav",
    StylePtr<InOutHelper<OnSpark<Green,White,850>,0,800>>(),
    StylePtr<Blue>(), "Luke-ish" },
  { "TeensySF", "tracks/venus.wav",
    StyleNormalPtr<Rainbow, WHITE, 300, 800>(),
    StylePtr<Blue>(), "JuBaseStyle2" },
  { "SmthGrey", "tracks/mercury.wav",
    StyleFirePtr<RED, YELLOW, 0>(),
    StylePtr<Blue>(), "fire" },
  { "SmthFuzz", "tracks/uranus.wav",
    StyleNormalPtr<Purple, WHITE, 300, 800>(),
    StylePtr<Blue>(), "purple" },
  { "RgueCmdr", "tracks/venus.wav",
    StyleNormalPtr<Blurple, AudioFlickerL<Yellow>, 300, 800>(),
    StylePtr<Blue>(), "Blurple" },
  { "", "",
    StyleNormalPtr<ColorCycle<Blue,0,1,Red,100,3000,5000>, WHITE, 300, 800>(),
    StylePtr<Blue>(), "Experimental" },
  { "BatteryLevel", "",
    &style_charging,
    StylePtr<Blue>(), "Battery\nLevel" },
  { "BatteryLevel", "",
    ChargingStylePtr<JuCharging>(),//TODOJU No on/off? Use mix to customize pulse?
    StylePtr<Blue>(), "Test" }
};
BladeConfig blades[] = {
  { 0,
    WS281XBladePtr<133, bladePin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3> >(),
    SimpleBladePtr<CH3LED, NoLED, NoLED, NoLED, bladePowerPin4, -1, -1, -1>(), // Bluetooth
    CONFIGARRAY(presets) },
};
#endif

#ifdef CONFIG_BUTTONS
Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");
Button AuxButton(BUTTON_AUX, auxPin, "aux");
#endif

#ifdef CONFIG_STYLES
template<class BASE_COLOR>
using JuBaseStyle = Layers<
  BASE_COLOR,
  AudioFlickerL<Rgb<0,210,0>>,//TODOJU Fonctionne seulement si la couleur de base est verte
  InOutTrL<TrWipe<300>,TrWipeIn<900>>,
  SimpleClashL<White>,
  ResponsiveBlastFadeL<White>,
  ResponsiveLockupL<White,TrInstant,TrInstant,Int<30000>,Int<4000>>,
  BlastFadeoutL<Yellow,800,EFFECT_FORCE>,
  ResponsiveMeltL<Mix<TwistAngle<>,Red,Yellow>,TrInstant,TrInstant>,
  ResponsiveStabL<White>,
  ResponsiveDragL<White>,
  ResponsiveLightningBlockL<White>
>;
template<class BASE_COLOR>
using JuBaseStyle2 = Layers<
  BASE_COLOR,
  AudioFlickerL<Rgb<210,210,0>>,
  OnSparkL<White,Int<500>>,
  InOutTrL<TrWipeSparkTip<White,300>,TrWipeInSparkTip<White,900>>,
  SimpleClashL<White>,
  OriginalBlastL<White>,
  LockupL<AudioFlickerL<White>>,
  BlastFadeoutL<Coral,800,EFFECT_FORCE>,
  ResponsiveMeltL<Mix<TwistAngle<>,Red,Yellow>,TrInstant,TrInstant>,
  ResponsiveStabL<White>,
  ResponsiveDragL<White>,
  ResponsiveLightningBlockL<White>
>;
template<class BASE_COLOR>
using Rotoscope = Layers<Mix<HoldPeakF<SwingSpeed<250>,Scale<SwingAcceleration<100>,Int<50>,Int<500>>,Scale<SwingAcceleration<>,Int<20000>,Int<10000>>>,RandomFlicker<StripesX<Int<15000>,Scale<HoldPeakF<SwingSpeed<200>,Scale<SwingAcceleration<100>,Int<50>,Int<300>>,Scale<SwingAcceleration<100>,Int<24000>,Int<16000>>>,Int<-3200>,Int<-200>>,RgbArg<BASE_COLOR_ARG,BASE_COLOR>,RgbArg<BASE_COLOR_ARG,BASE_COLOR>,Mix<Int<7710>,Black,RgbArg<BASE_COLOR_ARG,BASE_COLOR>>,RgbArg<BASE_COLOR_ARG,BASE_COLOR>,Mix<Int<19276>,Black,RgbArg<BASE_COLOR_ARG,BASE_COLOR>>>,RgbArg<BASE_COLOR_ARG,BASE_COLOR>>,RgbArg<BASE_COLOR_ARG,BASE_COLOR>>,TransitionEffectL<TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectRandomF<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Scale<EffectPosition<EFFECT_BLAST>,Int<28000>,Int<8000>>>,EFFECT_BLAST>,Mix<IsLessThan<ClashImpactF<>,Int<26000>>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<12000>,Int<60000>>>>,TrFadeX<Scale<ClashImpactF<>,Int<200>,Int<400>>>>,EFFECT_CLASH>,TransitionEffectL<TrWaveX<RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Int<100>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>>,EFFECT_CLASH>>,LockupTrL<TransitionEffect<AlphaL<AlphaMixL<Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<22000>>>,AudioFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<12000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,BrownNoiseFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<12000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>,300>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<22000>>>>,AlphaL<AudioFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<20000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,TrExtend<5000,TrInstant>,TrFade<5000>,EFFECT_LOCKUP_BEGIN>,TrConcat<TrJoin<TrDelay<50>,TrInstant>,Mix<IsLessThan<ClashImpactF<>,Int<26000>>,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<20000>,Int<60000>>>>>,TrFade<300>>,TrConcat<TrInstant,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,TrFade<400>>,SaberBase::LOCKUP_NORMAL,Int<1>>,ResponsiveLightningBlockL<Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Blue>,50,1>,TrConcat<TrExtend<200,TrInstant>,AlphaL<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Int<10000>,Int<21000>>,Int<10000>>>,TrFade<200>>,TrConcat<TrInstant,RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,TrFade<400>>,Int<1>>,LockupTrL<AlphaL<TransitionEffect<RandomPerLEDFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,255,255>>>,BrownNoiseFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,255,255>>,Int<300>>,TrExtend<4000,TrInstant>,TrFade<4000>,EFFECT_DRAG_BEGIN>,SmoothStep<Scale<TwistAngle<>,IntArg<DRAG_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrWipeIn<200>,TrWipe<200>,SaberBase::LOCKUP_DRAG,Int<1>>,LockupTrL<AlphaL<Stripes<2000,4000,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>,Mix<Sin<Int<50>>,Black,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>,Mix<Int<4096>,Black,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>>,SmoothStep<Scale<TwistAngle<>,IntArg<MELT_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrConcat<TrExtend<4000,TrWipeIn<200>>,AlphaL<HumpFlicker<Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>,RotateColorsX<Int<3000>,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>,100>,SmoothStep<Scale<TwistAngle<>,IntArg<MELT_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrFade<4000>>,TrWipe<200>,SaberBase::LOCKUP_MELT,Int<1>>,InOutTrL<TrWipeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,TrWipeInX<BendTimePowX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,Black>,TransitionEffectL<TrConcat<TrJoin<TrDelay<2000>,TrWipe<1000>>,AlphaL<Mix<BatteryLevel,Red,Green>,SmoothStep<BatteryLevel,Int<-10>>>,TrWipeIn<1000>>,EFFECT_BATTERY_LEVEL>>;
using JuCharging = Layers<Black, PulsingL<AlphaL<Mix<BatteryLevel,Red,Green>,SmoothStep<BatteryLevel,Int<-10>>>,Int<3000>>>;//TODOJU How to make value more stable??
#endif
