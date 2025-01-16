#pragma once
#include "GameManager.h"
#include "VampirePresenter.h"

/**
* @author   Suzuki N
* @date     24/11/05
* @note		StageModel�̒�`�t�@�C��
*/

class VampirePresenter;

/**
 * @class	StageModel
 * @brief   �X�e�[�W�I�u�W�F�N�g�̃��f��
 */
class StageModel
{
public:
	// �����o�ϐ�

	//! Player1�̃v���[���^�[�R���|�[�l���g
	VampirePresenter* player1_presenter;
	//! Player2�̃v���[���^�[�R���|�[�l���g
	VampirePresenter* player2_presenter;
	//! �J�����̒����_
	VECTOR viewPoint;

	//! ����ʒ[
	static float leftCorner;
	//! �E��ʒ[
	static float rightCorner;
};

