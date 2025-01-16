#include "AttackPresenter.h"


void AttackPresenter::CollisionSet(VampireModel* _model, const int _modelHandle, const int _centerFrame_right, const int _centerFrame_left, 
	const float _attackColRadius, const int _damage, const int _hitStun, const int _guardStun, AttackAttribute _attribute)
{
	model->vampireModel = _model;
	model->modelHandle = _modelHandle;
	model->attackColCenterFrame_right = _centerFrame_right;
	model->attackColCenterFrame_left = _centerFrame_left;
	model->attackColRadius = _attackColRadius;
	model->damage = _damage;
	model->hitStun = _hitStun;
	model->guardStun = _guardStun;
	model->attribute = _attribute;
	
	// �R���C�_�[�R���|�[�l���g���A�^�b�`
	model->attackCol = gameObject->AddComponent<HWCapsuleCollider>();

	model->attackCol->radius = model->attackColRadius;
	model->attackCol->isTrigger = true;
}


void AttackPresenter::Awake()
{
	gameObject->tag = (int)Tag::Attack;
	// ���f���̃C���X�^���X���쐬
	model = std::make_unique<AttackModel>();
	// View�R���|�[�l���g���A�^�b�`����
	view = gameObject->AddComponent<AttackView>();
	// �����I�ȏ������������s��
	view->Initialize();
}


void AttackPresenter::Update()
{
	//
	// �R���C�_�[�̈ʒu���X�V
	//

	// �E�����̏ꍇ
	if ((model->vampireModel->param & Parameter::Facing_Right) == Parameter::Facing_Right)
		model->attackCol->center = MV1GetFramePosition(model->modelHandle, model->attackColCenterFrame_right);
	else
		model->attackCol->center = MV1GetFramePosition(model->modelHandle, model->attackColCenterFrame_left);
}


void AttackPresenter::OnTriggerEnter(HWCollider& other)
{
	// �ΐ푊��̃R���C�_�[��Hit�����ꍇ
	if ((model->vampireModel->playerId == 1 && other.gameObject->tag == (int)Tag::Player_2) ||
		(model->vampireModel->playerId == 2 && other.gameObject->tag == (int)Tag::Player_1))
	{		
		//
		// �_���[�W�A�d������
		//

		//! ����̃L�����N�^�[�Ǘ��R���|�[�l���g������
		VampirePresenter* presenter = other.gameObject->GetComponent<VampirePresenter>();

		// �����Hit�������Ƃ�`���� �߂�l��Hit��Guard���𔻒�
		int isHit = presenter->AttackHit(this);

		// �_�E�����͖���
		if ((presenter->model->param & Parameter::Down) == Parameter::Down)
			return;

		// �p�����[�^��Hit�t���O�𗧂Ă�
		model->vampireModel->param |= Parameter::Hit;

		// �R���W������؂�
		CollisionDisable();
	}
}
