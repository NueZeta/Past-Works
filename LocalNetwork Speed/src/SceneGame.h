#pragma once
#include "SceneBase.h"

// �ǉ��̓ǂݍ��� -------------------

#include "TablePresenter.h"
#include "CardManager.h"
#include "Player.h"

// ----------------------------------

/**
* @author   Suzuki N
* @date     24/11/20
* @note		SceneGame�̒�`�t�@�C��
*/


/**
 * @class	SceneGame
 * @brief   ���C���Q�[���V�[��
 */
class SceneGame : public SceneBase 
{
private:
	//�����o�ϐ�

	HWGameObject* CM;

	HWGameObject* table;

	HWGameObject* player;

	bool isConnect = false;
	bool isConnected = false;
	int netHandle = -2;
	int connectTime = 0;
	int resultTime = 0;


public:
	// ���\�b�h

	/**
	 * @brief       �R���X�g���N�^
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	SceneGame();

	/**
	 * @brief       �f�X�g���N�^
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	~SceneGame() override;

	/**
	 * @brief       ��F�Ă΂�郁�\�b�h
	 * @author      Suzuki N
	 * @date        24/11/20
	 */
	void Update() override;
};

