#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Stage.h"

/**
* @author   Suzuki N
* @date     24/10/01
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

	//! �v���C���[�I�u�W�F�N�g
	std::unique_ptr<Player> player;
	//! �G�l�~�[�Ǘ��p�̃I�u�W�F�N�g
	std::unique_ptr<HWGameObject> enemyManager;
	//! �G�l�~�[�Ǘ��p�̃R���|�[�l���g
	EnemyManager* eneManagerCp;
	//! �X�e�[�W�I�u�W�F�N�g
	std::unique_ptr<HWGameObject> stage;

	//! Player�@���j�󂳂ꂽ����
	int crashTime;
	//! �N���A�����Ƃ��̎���
	int clearTime;


public:
	// ���\�b�h

	static void Init();

	// �R���X�g���N�^
	SceneGame(InputSystem* _Input);

	// �f�X�g���N�^
	~SceneGame() override;

	// ��F�Ă΂��֐�
	// �I�[�o���C�h���\�b�h
	void Update() override;
};

