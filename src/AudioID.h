#ifndef AudioID_h__
#define AudioID_h__

/*!
 * \file AudioID.h
 * \date 2014/08/26 16:10
 *
 * \author lunchunliu
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: “Ù∆µid¿‡
 *
 * \note
*/



class AudioID
{
private:
	AudioID();
	~AudioID();

	static AudioID* m_instance;

public:
	static AudioID* getInstance();

	static unsigned m_audio_bridge;
	static unsigned m_audio_bullet;
	static unsigned m_audio_button_click;
	static unsigned m_audio_change_character;
	static unsigned m_audio_game_over;
	static unsigned m_audio_gate;
	static unsigned m_audio_jump;
	static unsigned m_audio_logo;
	static unsigned m_audio_monkey_2nd_jump;
	static unsigned m_audio_monkey_fight;
	static unsigned m_audio_pig_fight;
	static unsigned m_audio_pig_push;
	static unsigned m_audio_stone;
	static unsigned m_audio_success;
};
#endif // AudioID_h__


