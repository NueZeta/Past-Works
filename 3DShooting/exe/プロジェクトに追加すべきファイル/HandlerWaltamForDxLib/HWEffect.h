#pragma once
#include "HandlerWaltanForDxLib.h"



/**
* @author   Suzuki N
* @date     24/09/15
* @note		�G�t�F�N�g�R���|�[�l���g�̒�`
*/


/**
 * @enum	StopAction
 * @brief	�Đ��I�����̃A�N�V����
 */
enum class StopAction
{
	//! �������Ȃ�(0)
	None,
	//! ���[�v����(1)
	Loop,
	//! �폜����(2)
	Destroy,
	//! ��A�N�e�B�u�ɂ���(3)
	Disable,
	//! �R�[���o�b�N�֐����Ă�(4)
	Callback,
};


/**
 * @class	HWSphereCollider
 * @brief	�G�t�F�N�g�R���|�[�l���g
 */
class HWEffect : public HWComponent
{
private:
	// �����o�ϐ�

	/**
	 * @brief		�G�t�F�N�g�n���h��
	 * @History		24/10/07 �쐬(Suzuki N)
	 */
	int effectResourceHandle;

	/**
	 * @brief		�Đ����̃G�t�F�N�g�n���h��
	 * @History		24/10/07 �쐬(Suzuki N)
	 */
	int playingEffectHandle;

	/**
	 * @brief		�Đ����x
	 * @History		24/10/07 �쐬(Suzuki N)
	 */
	float playSpeed;

	/**
	 * @brief		�Đ�����
	 * @History		24/10/07 �쐬(Suzuki N)
	 */
	bool isPlay;

	/**
	 * @brief		�Đ��I�����̃R�[���o�b�N�֐�
	 * @History		24/10/07 �쐬(Suzuki N)
	 */
	std::function<void()> CallBack;

	struct Color
	{
		unsigned int r, g, b, a;
	};

	/**
	 * @brief		�J���[
	 * @History		24/10/07 �쐬(Suzuki N)
	 */
	Color color;

public:

	/**
	 * @brief		�Đ��I�����̃A�N�V����
	 * @History		24/10/07 �쐬(Suzuki N)
	 */
	StopAction stopAction;


public:
	// ���\�b�h

	HWEffect(const std::string& _path, const float _size = 1.0f);
	~HWEffect();

#pragma region Getter�֐�

	/**
	 * @brief		�Đ��󋵂��擾����
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	bool IsPlay() { return isPlay; }

	/**
	 * @brief		�G�t�F�N�g�̍Đ����x���擾����
	 * @return		float �Đ����x
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	float GetPlaySpeed()
	{
		return GetSpeedPlayingEffekseer3DEffect(playingEffectHandle);
	}

	/**
	 * @brief		�Đ����̃G�t�F�N�g�n���h��
	 * @return		int �G�t�F�N�g�n���h��
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	int GetPlayEffectHandle() { return playingEffectHandle; }

#pragma endregion

#pragma region Setter�֐�

	/**
	 * @brief		�G�t�F�N�g���Đ�����
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	void Play();

	/**
	 * @brief		�Đ����~����
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	void Stop();

	/**
	 * @brief		�G�t�F�N�g�̍Đ����x��ݒ肷��
	 * @rparam[in]	const float �Đ����x
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	void SetPlaySpeed(float _speed)
	{
		SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, _speed);
		_speed = _speed;
	}

	/**
	 * @brief		�G�t�F�N�g�Đ��I�����ɌĂ΂��R�[���o�b�N�֐���o�^����
	 * @rparam[in]	std::function<void()> �o�^����R�[���o�b�N�֐�
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	void SetCallBack(std::function<void()> _callBack)
	{
		CallBack = _callBack;
	}

	/**
	 * @brief		�G�t�F�N�g�̃J���[��ݒ肷��
	 * @rparam[in]	const Color& �J���[
	 * @author		Suzuki N
	 * @date		24/10/07
	 */
	void SetColor(const int r, const int g, const int b, const int a)
	{
		if(playingEffectHandle != -1)
		{
			SetColorPlayingEffekseer3DEffect(playingEffectHandle, r, g, b, a);
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;			
		}
	}

#pragma endregion



	void Awake()override;
	void Start()override;
	void Update()override;
};

