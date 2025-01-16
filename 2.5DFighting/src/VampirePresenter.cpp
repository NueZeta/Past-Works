#include "VampirePresenter.h"




void VampirePresenter::AnimChange()
{
	//
	// �E�����̏ꍇ
	//
	if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		//
		// �K�E�Z
		//
		{
			// Special_1
			if ((model->param & Parameter::Special_1) == Parameter::Special_1)
				view->animator->AnimChange((int)VampireAnim::SpFireBall);
			// Special_2
			if ((model->param & Parameter::Special_2) == Parameter::Special_2)
				view->animator->AnimChange((int)VampireAnim::SpDragonUpper);
		}

		//
		// �������
		//
		if ((model->param & Parameter::Crouching) == Parameter::Neutral)
		{
			// �K�[�h��
			if ((model->param & Parameter::Blockstun) == Parameter::Blockstun)
				view->animator->AnimChange((int)VampireAnim::StGuard);
			// �q�b�g��
			else if ((model->param & Parameter::Hitstun) == Parameter::Hitstun)
				view->animator->AnimChange((int)VampireAnim::StDamage);

			// ���U��
			else if ((model->param & Parameter::Ha) == Parameter::Ha)
				view->animator->AnimChange((int)VampireAnim::StHa);
			// ��U��
			else if ((model->param & Parameter::La) == Parameter::La)
				view->animator->AnimChange((int)VampireAnim::StLa);

			// ����
			else if ((model->param & Parameter::Walk) == Parameter::Walk)
				view->animator->AnimChange((int)VampireAnim::StWalk);
			// ���
			else if ((model->param & Parameter::Back) == Parameter::Back)
				view->animator->AnimChange((int)VampireAnim::StBack);
			else
				view->animator->AnimChange((int)VampireAnim::StIdol);
		}

		//
		// ���Ⴊ�ݏ��
		//
		else if ((model->param & Parameter::Crouching) == Parameter::Crouching)
		{
			// �K�[�h��
			if ((model->param & Parameter::Blockstun) == Parameter::Blockstun)
				view->animator->AnimChange((int)VampireAnim::CrGuard);
			// �q�b�g��
			else if ((model->param & Parameter::Hitstun) == Parameter::Hitstun)
				view->animator->AnimChange((int)VampireAnim::CrDamage);

			// ���U��
			else if ((model->param & Parameter::Ha) == Parameter::Ha)
				view->animator->AnimChange((int)VampireAnim::CrHa);
			// ��U��
			else if ((model->param & Parameter::La) == Parameter::La)
				view->animator->AnimChange((int)VampireAnim::CrLa);
			else
				view->animator->AnimChange((int)VampireAnim::CrIdol);
		}
	}

	//
	// �������̏ꍇ
	//
	else
	{
		//
		// �K�E�Z
		//
		{
			// Special_1
			if ((model->param & Parameter::Special_1) == Parameter::Special_1)
				view->animator->AnimChange((int)VampireAnim::SpFireBall + (int)VampireAnim::Left);
			// Special_2
			if ((model->param & Parameter::Special_2) == Parameter::Special_2)
				view->animator->AnimChange((int)VampireAnim::SpDragonUpper + (int)VampireAnim::Left);
		}

		//
		// �������
		//
		if ((model->param & Parameter::Crouching) == Parameter::Neutral)
		{
			// �K�[�h��
			if ((model->param & Parameter::Blockstun) == Parameter::Blockstun)
				view->animator->AnimChange((int)VampireAnim::StGuard + (int)VampireAnim::Left);
			// �K�[�h��
			else if ((model->param & Parameter::Hitstun) == Parameter::Hitstun)
				view->animator->AnimChange((int)VampireAnim::StDamage + (int)VampireAnim::Left);

			// ���U��
			else if ((model->param & Parameter::Ha) == Parameter::Ha)
				view->animator->AnimChange((int)VampireAnim::StHa + (int)VampireAnim::Left);
			// ��U��
			else if ((model->param & Parameter::La) == Parameter::La)
				view->animator->AnimChange((int)VampireAnim::StLa + (int)VampireAnim::Left);

			// ����
			else if ((model->param & Parameter::Walk) == Parameter::Walk)
				view->animator->AnimChange((int)VampireAnim::StWalk + (int)VampireAnim::Left);
			// ���
			else if ((model->param & Parameter::Back) == Parameter::Back)
				view->animator->AnimChange((int)VampireAnim::StBack + (int)VampireAnim::Left);
			else
				view->animator->AnimChange((int)VampireAnim::StIdol + (int)VampireAnim::Left);
		}

		//
		// ���Ⴊ�ݏ��
		//
		else if ((model->param & Parameter::Crouching) == Parameter::Crouching)
		{
			// �K�[�h��
			if ((model->param & Parameter::Blockstun) == Parameter::Blockstun)
				view->animator->AnimChange((int)VampireAnim::CrGuard + (int)VampireAnim::Left);
			// �K�[�h��
			else if ((model->param & Parameter::Hitstun) == Parameter::Hitstun)
				view->animator->AnimChange((int)VampireAnim::CrDamage + (int)VampireAnim::Left);

			// ���U��
			else if ((model->param & Parameter::Ha) == Parameter::Ha)
				view->animator->AnimChange((int)VampireAnim::CrHa + (int)VampireAnim::Left);
			// ��U��
			else if ((model->param & Parameter::La) == Parameter::La)
				view->animator->AnimChange((int)VampireAnim::CrLa + (int)VampireAnim::Left);
			else
				view->animator->AnimChange((int)VampireAnim::CrIdol + (int)VampireAnim::Left);
		}
	}
}


void VampirePresenter::ParameterSet()
{
	// �L�[���͂��Ȃ��ꍇ�͖���
	if (model->keyHistory.size() <= 0) return;

	// �W�����v���͖���
	if ((model->param & Parameter::Jump) == Parameter::Jump)
		return;

	// �_���[�W���[�V�������A�K�[�h���[�V�������͖���
	if ((model->param & Parameter::Hitstun) == Parameter::Hitstun ||
		(model->param & Parameter::Blockstun) == Parameter::Blockstun)
	{
		// �ړ��p�����[�^������
		model->param &= ~Parameter::Walk;
		model->param &= ~Parameter::Back;

		return;
	}


	// �ŐV�̓���
	auto crrKey = model->keyHistory[model->keyHistory.size() - 1];

	// ���݂̍U���R�}���h������1F�ڂ̏ꍇ�̂݁A�p�����[�^�ɃZ�b�g����
	if (model->keyHistory.size() > 1)
	{
		if ((crrKey & (InputKey::Ha | InputKey::La)) == InputKey::Neutral)
			model->crrInputParam &= ~(Parameter::Ha | Parameter::La);
		else if (((crrKey & model->keyHistory[model->keyHistory.size() - 2]) &
			(InputKey::Ha | InputKey::La)) != InputKey::Neutral)
			model->crrInputParam &= ~(Parameter::Ha | Parameter::La);
		else
		{
			if ((crrKey & InputKey::Ha) == InputKey::Ha)
				model->crrInputParam |= Parameter::Ha;
			else if ((crrKey & InputKey::La) == InputKey::La)
				model->crrInputParam |= Parameter::La;
		}
	}


	//
	// �U���s�����̏���
	//

	if ((model->param & Parameter::La) == Parameter::La ||
		(model->param & Parameter::Ha) == Parameter::Ha ||
		(model->param & Parameter::Special_1) == Parameter::Special_1 ||
		(model->param & Parameter::Special_2) == Parameter::Special_2)
	{
		// �ړ��p�����[�^������
		model->param &= ~Parameter::Walk;
		model->param &= ~Parameter::Back;

		// Hit or Guard���̏ꍇ
		if ((model->param & Parameter::Hit) == Parameter::Hit)
		{
			// Ha�̓��͂�������
			if ((model->crrInputParam & Parameter::Ha) == Parameter::Ha)
			{
				//
				// �K�E�Z�ŃL�����Z��
				//

				Parameter param = CommandCheck(Parameter::Ha);
				if ((param & Parameter::Special_1) == Parameter::Special_1)
					view->animator->AnimChange((int)VampireAnim::SpFireBall, true);
			}
		}

		return;
	}


	// Ha���͂�������
	if ((model->crrInputParam & Parameter::Ha) == Parameter::Ha)
		model->param |= CommandCheck(Parameter::Ha);

	// La���͂�������
	if ((model->crrInputParam & Parameter::La) == Parameter::La)
		model->param |= Parameter::La;

	// �����͂�������
	if ((crrKey & InputKey::Up) == InputKey::Up)
		model->param |= Parameter::Jump;

	// �����͂�������
	if ((crrKey & InputKey::Down) == InputKey::Down)
		model->param |= Parameter::Crouching;
	else
		model->param &= ~Parameter::Crouching;


	// �����͂�������
	if ((crrKey & InputKey::Left) == InputKey::Left)
	{
		if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
			model->param |= Parameter::Back;
		else
			model->param |= Parameter::Walk;
	}
	else
	{
		if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
			model->param &= ~Parameter::Back;
		else
			model->param &= ~Parameter::Walk;
	}

	// �����͂�����
	if ((crrKey & InputKey::Right) == InputKey::Right)
	{
		if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
			model->param |= Parameter::Walk;
		else
			model->param |= Parameter::Back;
	}
	else
	{
		if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
			model->param &= ~Parameter::Walk;
		else
			model->param &= ~Parameter::Back;
	}
}


const Parameter VampirePresenter::CommandCheck(const Parameter& _param)
{
	//
	// �E�������Ă���ꍇ 
	//

	if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		//
		// 623�R�}���h�̃R�}���h���������Ă��邩������
		//

		{
			// �L�[���͋L�^���Â����̂���R�}���h�̌���
			for (auto it = model->keyHistory.begin(); it != model->keyHistory.end(); ++it)
				// �ŏ��̃R�}���h -> 6 �����o����
				if (*it == InputKey::Right)
				{
					for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
					{
						if (*it2 == InputKey::Down)
						{
							// �L�[���͋L�^���Â����̂���R�}���h�̌���
							for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
							{
								//
								// 623�R�}���h����
								//
								if (*it2 == (InputKey::Right | InputKey::Down))
									return Parameter::Special_2;
							}
						}

						// �t�����̓��͂����m����ƃR�}���h�~�X
						if (*it2 == InputKey::Left)
							return _param;
					}
					break;
				}
		}


		//
		// 236�R�}���h�̃R�}���h���������Ă��邩������
		//

		{
			if(model->projectile == nullptr)
			{
				// �L�[���͋L�^���Â����̂���R�}���h�̌���
				for (auto it = model->keyHistory.begin(); it != model->keyHistory.end(); ++it)
					// �ŏ��̃R�}���h -> 2 �����o����
					if (*it == InputKey::Down)
					{
						for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
						{
							// 236�R�}���h����
							if (*it2 == InputKey::Right)
								return Parameter::Special_1;

							// �t�����̓��͂����m����ƃR�}���h�~�X
							if (*it2 == InputKey::Left)
								return _param;
						}
						break;
					}
			}
		}


		//
		// 214�R�}���h�̃R�}���h���������Ă��邩������
		//

		{
			// �L�[���͋L�^���Â����̂���R�}���h�̌���
			for (auto it = model->keyHistory.begin(); it != model->keyHistory.end(); ++it)
				// �ŏ��̃R�}���h -> 2 �����o����
				if (*it == InputKey::Down)
				{
					for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
					{
						// 214�R�}���h����
						if (*it2 == InputKey::Left)
							return _param;

						// �t�����̓��͂����m����ƃR�}���h�~�X
						if (*it2 == InputKey::Right)
							return _param;
					}
					break;
				}
		}
	}

	//
	// ���������Ă���ꍇ
	//
	else if ((model->param & Parameter::Facing_Right) == Parameter::Neutral)
	{
		//
		// 421�R�}���h�̃R�}���h���������Ă��邩������
		//

		{
			// �L�[���͋L�^���Â����̂���R�}���h�̌���
			for (auto it = model->keyHistory.begin(); it != model->keyHistory.end(); ++it)
				// �ŏ��̃R�}���h -> 6 �����o����
				if (*it == InputKey::Left)
				{
					for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
					{
						if (*it2 == InputKey::Down)
						{
							// �L�[���͋L�^���Â����̂���R�}���h�̌���
							for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
							{
								//
								// 623�R�}���h����
								//
								if (*it2 == (InputKey::Left | InputKey::Down))
									return Parameter::Special_2;
							}
						}

						// �t�����̓��͂����m����ƃR�}���h�~�X
						if (*it2 == InputKey::Right)
							return _param;
					}
					break;
				}
		}


		//
		// 236�R�}���h�̃R�}���h���������Ă��邩������
		//

		{
			if (model->projectile == nullptr)
			{

				// �L�[���͋L�^���Â����̂���R�}���h�̌���
				for (auto it = model->keyHistory.begin(); it != model->keyHistory.end(); ++it)
					// �ŏ��̃R�}���h -> 2 �����o����
					if (*it == InputKey::Down)
					{
						for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
						{
							// 236�R�}���h����
							if (*it2 == InputKey::Left)
								return Parameter::Special_1;

							// �t�����̓��͂����m����ƃR�}���h�~�X
							if (*it2 == InputKey::Right)
								return _param;
						}
						break;
					}
			}
		}


		//
		// 214�R�}���h�̃R�}���h���������Ă��邩������
		//

		{
			// �L�[���͋L�^���Â����̂���R�}���h�̌���
			for (auto it = model->keyHistory.begin(); it != model->keyHistory.end(); ++it)
				// �ŏ��̃R�}���h -> 2 �����o����
				if (*it == InputKey::Down)
				{
					for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
					{
						//
						// 214�R�}���h����
						//

						if (*it2 == InputKey::Right)
							return _param;

						// �t�����̓��͂����m����ƃR�}���h�~�X
						if (*it2 == InputKey::Left)
							return _param;
					}
					break;
				}
		}
	}


	// �R�}���h���������Ă��Ȃ������ꍇ�́A���������̂܂ܕԂ�
	return _param;
}


void VampirePresenter::OnKeyCheck(InputAction::CallBackContext& context)
{
	if ((GameManager::param & GameParam::Game) != GameParam::Game) return;

	// ���̃t���[���ł̓���
	InputKey key = InputKey::Neutral;

	// �R�}���h����͊J�n or ���͒� �̏ꍇ
	if (context.state == InputState::Started || context.state == InputState::Performed)
	{
		// ���� -> 2
		if (context.dInput.Y > 100)
			key |= InputKey::Down;
		else
			key &= ~InputKey::Down;

		// ���� -> 2
		if (context.dInput.Y < -100)
			key |= InputKey::Up;
		else
			key &= ~InputKey::Up;

		// ���� -> 4
		if (context.dInput.X < -100)
			key |= InputKey::Left;
		else
			key &= ~InputKey::Left;

		// ���� -> 6
		if (context.dInput.X > 100)
			key |= InputKey::Right;
		else
			key &= ~InputKey::Right;
	}

	for (auto it = context.key.begin(); it != context.key.end(); ++it)
	{
		// �R�}���h����͊J�n or ���͒� �̏ꍇ
		if (it->inputState == InputState::Started || it->inputState == InputState::Performed)
		{
			// ���� -> La
			if ((it->keyCode & PAD_INPUT_1) == PAD_INPUT_1)
				key |= InputKey::La;
			// ���� -> Ha
			if ((it->keyCode & PAD_INPUT_2) == PAD_INPUT_2)
				key |= InputKey::Ha;
		}
		// ���͉���
		else if (it->inputState == InputState::Canceled)
		{
			// ���� -> La
			if ((it->keyCode & PAD_INPUT_1) == PAD_INPUT_1)
				key &= ~InputKey::La;
			// ���� -> Ha
			if ((it->keyCode & PAD_INPUT_2) == PAD_INPUT_2)
				key &= ~InputKey::Ha;
		}
	}

	model->keyHistory.push_back(key);
}


void VampirePresenter::Dead()
{
	Time::SetTargetFPS(20);
	GameManager::param = GameParam::KO;

	model->param &= Parameter::Facing_Right;
	
	if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
		view->animator->AnimChange((int)VampireAnim::Down, true);
	else
		view->animator->AnimChange((int)VampireAnim::Down + (int)VampireAnim::Left, true);
}


void VampirePresenter::Move()
{
	// ����,��W�����v��Ԃ݈̂ړ��������s��
	if ((model->param & (Parameter::Crouching | Parameter::Jump)) == Parameter::Neutral)
	{
		//
		// �E�����̏ꍇ
		// 
		if((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
		{
			// �O����
			if ((model->param & Parameter::Walk) == Parameter::Walk)
				if(transform->position.x < StageModel::rightCorner)
					transform->velocity.x += WALK_SPEED;
			// ������
			if ((model->param & Parameter::Back) == Parameter::Back)
				if(transform->position.x > StageModel::leftCorner)
					transform->velocity.x -= BACK_SPEED;
		}
		//
		// �������̏ꍇ
		// 
		else
		{
			// �O����
			if ((model->param & Parameter::Walk) == Parameter::Walk)
				if (transform->position.x > StageModel::leftCorner)
					transform->velocity.x -= WALK_SPEED;
			// ������
			if ((model->param & Parameter::Back) == Parameter::Back)
				if (transform->position.x < StageModel::rightCorner)
					transform->velocity.x += BACK_SPEED;
		}
	}
}


void VampirePresenter::Jump()
{
	// �W�����v���ȊO�͖���
	if ((model->param & Parameter::Jump) != Parameter::Jump) return;

	// �W�����v�͂� 0 �̏ꍇ�A�V���ɃW�����v�͂�ݒ肷��
	if (model->jumpPower == 0.0f)
	{
		model->jumpPower = 18.0f;
		// �A�j���[�V������ύX
		view->animator->AnimChange((int)VampireAnim::Jump, true);

		//
		// �G�t�F�N�g�Đ�
		//

		// Guard���̃G�t�F�N�g�Đ�
		HWGameObject* effect = new HWGameObject("HitEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/JumpEffect.efkefc", 10.f);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
		info->SetPlaySpeed(5.0f);
	}

	// �d�͕��̌��Z
	model->jumpPower -= 0.7f;

	//! �ړ��x�N�g��
	VECTOR velocity = VGet(0, model->jumpPower, 0);

	// �O��W�����v�̏ꍇ�A���̕������Z
	if (((model->param & Parameter::Facing_Right) == Parameter::Facing_Right && 
		(model->param & Parameter::Walk) == Parameter::Walk) || 
		((model->param & Parameter::Facing_Right) == Parameter::Neutral &&
		(model->param & Parameter::Back) == Parameter::Back))
		if (transform->position.x < StageModel::rightCorner)
			velocity.x = WALK_SPEED * 1.5f;

	if (((model->param & Parameter::Facing_Right) == Parameter::Neutral &&
		(model->param & Parameter::Walk) == Parameter::Walk) ||
		((model->param & Parameter::Facing_Right) == Parameter::Facing_Right &&
		(model->param & Parameter::Back) == Parameter::Back))
		if (transform->position.x > StageModel::leftCorner)
			velocity.x = -WALK_SPEED * 1.5f;

	// ���W��ύX
	transform->position += velocity;

	// �n�ʂɒ��n����
	if (transform->position.y <= GROUND)
	{
		transform->position.y = GROUND;

		if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
			view->animator->AnimChange((int)VampireAnim::Landing + (int)VampireAnim::Left, true);
		else
			view->animator->AnimChange((int)VampireAnim::Landing, true);
	}
}


void VampirePresenter::AttackAnimEnd()
{
	//
	// �U���ƕK�E�Z�̃p�����[�^�����ׂĉ���
	//

	model->param &= ~Parameter::Ha;
	model->param &= ~Parameter::La;
	model->param &= ~Parameter::Special_1;
	model->param &= ~Parameter::Hit;


	// ���Ⴊ�ݒ��̏ꍇ�A�Đ��I�����̃f�t�H���g�A�j���[�V���������Ⴊ�݂ɕύX
	if ((model->param &= Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		if ((model->param & Parameter::Crouching) == Parameter::Crouching)
			view->animator->SetDefaultAnimId((int)VampireAnim::CrIdol);
		// ����ȊO�͗����A�j���[�V�������Z�b�g
		else
			view->animator->SetDefaultAnimId((int)VampireAnim::StIdol);
	}
	else
	{
		if ((model->param & Parameter::Crouching) == Parameter::Crouching)
			view->animator->SetDefaultAnimId((int)VampireAnim::CrIdol + (int)VampireAnim::Left);
		// ����ȊO�͗����A�j���[�V�������Z�b�g
		else
			view->animator->SetDefaultAnimId((int)VampireAnim::StIdol + (int)VampireAnim::Left);
	}
}


void VampirePresenter::GuardAnimEnd()
{
	//
	// �K�[�h�̃p�����[�^�����ׂĉ���
	//

	model->param &= ~Parameter::Guard;
	model->param &= ~Parameter::Blockstun;


	// ���Ⴊ�ݒ��̏ꍇ�A�Đ��I�����̃f�t�H���g�A�j���[�V���������Ⴊ�݂ɕύX
	if ((model->param &= Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		if ((model->param & Parameter::Crouching) == Parameter::Crouching)
			view->animator->SetDefaultAnimId((int)VampireAnim::CrIdol);
		// ����ȊO�͗����A�j���[�V�������Z�b�g
		else
			view->animator->SetDefaultAnimId((int)VampireAnim::StIdol);
	}
	else
	{
		if ((model->param & Parameter::Crouching) == Parameter::Crouching)
			view->animator->SetDefaultAnimId((int)VampireAnim::CrIdol + (int)VampireAnim::Left);
		// ����ȊO�͗����A�j���[�V�������Z�b�g
		else
			view->animator->SetDefaultAnimId((int)VampireAnim::StIdol + (int)VampireAnim::Left);
	}
}


void VampirePresenter::HitAnimEnd()
{
	//
	// �q�b�g���̃p�����[�^�����ׂĉ���
	//

	model->param &= ~Parameter::Hitstun;

	// ���Ⴊ�ݒ��̏ꍇ�A�Đ��I�����̃f�t�H���g�A�j���[�V���������Ⴊ�݂ɕύX
	if ((model->param &= Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		if ((model->param & Parameter::Crouching) == Parameter::Crouching)
			view->animator->SetDefaultAnimId((int)VampireAnim::CrIdol);
		// ����ȊO�͗����A�j���[�V�������Z�b�g
		else
			view->animator->SetDefaultAnimId((int)VampireAnim::StIdol);
	}
	else
	{
		if ((model->param & Parameter::Crouching) == Parameter::Crouching)
			view->animator->SetDefaultAnimId((int)VampireAnim::CrIdol + (int)VampireAnim::Left);
		// ����ȊO�͗����A�j���[�V�������Z�b�g
		else
			view->animator->SetDefaultAnimId((int)VampireAnim::StIdol + (int)VampireAnim::Left);
	}
}


bool VampirePresenter::AttackHit(const AttackPresenter* _attackPresenter)
{
	//
	// �A�j���[�V�����̍Đ����x��ݒ�
	//

	//! �A�j���[�V�����̔z��
	auto& animInfoVec = view->animator->GetAnimInfoVec();

	//! �����q�b�g���̃A�j���[�V�����̍Đ����x���v�Z
	double stHitAnimPlaySpeed = animInfoVec[(int)VampireAnim::StDamage]->totalTime / (double)_attackPresenter->model->hitStun;
	//! ���q�b�g���̃A�j���[�V�����̍Đ����x���v�Z
	double crHitAnimPlaySpeed = animInfoVec[(int)VampireAnim::CrDamage]->totalTime / (double)_attackPresenter->model->hitStun;
	//! �����K�[�h���̃A�j���[�V�����̍Đ����x���v�Z
	double stGuardAnimPlaySpeed = animInfoVec[(int)VampireAnim::StGuard]->totalTime / (double)_attackPresenter->model->guardStun;
	//! ���K�[�h���̃A�j���[�V�����̍Đ����x���v�Z
	double crGuardAnimPlaySpeed = animInfoVec[(int)VampireAnim::CrGuard]->totalTime / (double)_attackPresenter->model->guardStun;

	if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		animInfoVec[(int)VampireAnim::StDamage]->playSpeed = stHitAnimPlaySpeed;
		animInfoVec[(int)VampireAnim::CrDamage]->playSpeed = crHitAnimPlaySpeed;
		animInfoVec[(int)VampireAnim::StGuard]->playSpeed = stGuardAnimPlaySpeed;
		animInfoVec[(int)VampireAnim::CrGuard]->playSpeed = crGuardAnimPlaySpeed;
	}
	else
	{
		animInfoVec[(int)VampireAnim::StDamage + (int)VampireAnim::Left]->playSpeed = stHitAnimPlaySpeed;
		animInfoVec[(int)VampireAnim::CrDamage + (int)VampireAnim::Left]->playSpeed = crHitAnimPlaySpeed;
		animInfoVec[(int)VampireAnim::StGuard + (int)VampireAnim::Left]->playSpeed = stGuardAnimPlaySpeed;
		animInfoVec[(int)VampireAnim::CrGuard + (int)VampireAnim::Left]->playSpeed = crGuardAnimPlaySpeed;
	}


	//
	// Guard�̏ꍇ
	//
			/*  ��i  */
	if ((((model->param & Parameter::Back) == Parameter::Back || (model->param & Parameter::Blockstun) == Parameter::Blockstun) &&
			(_attackPresenter->model->attribute & AttackAttribute::LowAttack | AttackAttribute::OverheadAttack) == AttackAttribute::None) || 
			/*  ���i  */
		(((model->param & Parameter::Back) == Parameter::Back || (model->param & Parameter::Blockstun) == Parameter::Blockstun) &&
			((_attackPresenter->model->attribute & AttackAttribute::LowAttack) == AttackAttribute::LowAttack) && (model->param & Parameter::Crouching) == Parameter::Crouching) ||
			/*  ���i  */
		(((model->param & Parameter::Back) == Parameter::Back || (model->param & Parameter::Blockstun) == Parameter::Blockstun) &&
			((_attackPresenter->model->attribute & AttackAttribute::OverheadAttack) == AttackAttribute::OverheadAttack) && (model->param & Parameter::Crouching) == Parameter::Neutral))
	{
		// �p�����[�^���K�[�h�ɐ؂�ւ���
		model->param |= Parameter::Guard;
		model->param |= Parameter::Blockstun;

		//
		// �G�t�F�N�g�Đ�
		//

		// Guard���̃G�t�F�N�g�Đ�
		HWGameObject* effect = new HWGameObject("HitEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/HitEffect.efkefc", 10.f);
		effect->transform->position = _attackPresenter->model->attackCol->center;
		info->stopAction = StopAction::Destroy;
		info->Play();


		// ���ʂ�Ԃ�(Guard)
		return false;
	}
	//
	// Hit�̏ꍇ
	//
	else
	{
		// �_���[�W����
		model->hp -= _attackPresenter->model->damage;

		//
		// �G�t�F�N�g�Đ�
		//

		// Hit���̃G�t�F�N�g�Đ�
		HWGameObject* effect = new HWGameObject("HitEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/HitEffect2.efkefc", 10.f);
		effect->transform->position = _attackPresenter->model->attackCol->center;

		if((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
			effect->transform->rotate = VGet(0,90,0);
		else
			effect->transform->rotate = VGet(0,-90,0);

		info->stopAction = StopAction::Destroy;
		info->Play();


		// hp��0�ɂȂ����ꍇ
		if (model->hp <= 0)
		{
			model->hp = 0;
			Dead();
		}

		// �_�E�������̍U���̏ꍇ�A�_�E���p�����[�^��t�^����
		if ((_attackPresenter->model->attribute & AttackAttribute::KnockDown) == AttackAttribute::KnockDown)
		{
			//model->param |= Parameter::Down;
			//view->animator->AnimChange((int)VampireAnim::Down, true);
		}

		// �A���q�b�g
		if((model->param & Parameter::Hitstun) == Parameter::Hitstun)
		{
			if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
				view->animator->AnimChange((int)VampireAnim::StDamage + (int)VampireAnim::Left, true);
			else
				view->animator->AnimChange((int)VampireAnim::StDamage, true);
		}
		else
			// �p�����[�^���q�b�g�ɐ؂�ւ���
			model->param |= Parameter::Hitstun;

		view->animator->blendSpeed = 0.3f;

		// ���ʂ�Ԃ�(Hit)
		return true;
	}
}


bool VampirePresenter::AttackHit(const ProjectilePresenter* _attackPresenter)
{
	//
	// �A�j���[�V�����̍Đ����x��ݒ�
	//

	//! �A�j���[�V�����̔z��
	auto& animInfoVec = view->animator->GetAnimInfoVec();

	//! �����q�b�g���̃A�j���[�V�����̍Đ����x���v�Z
	double stHitAnimPlaySpeed = animInfoVec[(int)VampireAnim::StDamage]->totalTime / (double)_attackPresenter->model->hitStun;
	//! ���q�b�g���̃A�j���[�V�����̍Đ����x���v�Z
	double crHitAnimPlaySpeed = animInfoVec[(int)VampireAnim::CrDamage]->totalTime / (double)_attackPresenter->model->hitStun;
	//! �����K�[�h���̃A�j���[�V�����̍Đ����x���v�Z
	double stGuardAnimPlaySpeed = animInfoVec[(int)VampireAnim::StGuard]->totalTime / (double)_attackPresenter->model->guardStun;
	//! ���K�[�h���̃A�j���[�V�����̍Đ����x���v�Z
	double crGuardAnimPlaySpeed = animInfoVec[(int)VampireAnim::CrGuard]->totalTime / (double)_attackPresenter->model->guardStun;

	if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		animInfoVec[(int)VampireAnim::StDamage]->playSpeed = stHitAnimPlaySpeed;
		animInfoVec[(int)VampireAnim::CrDamage]->playSpeed = crHitAnimPlaySpeed;
		animInfoVec[(int)VampireAnim::StGuard]->playSpeed = stGuardAnimPlaySpeed;
		animInfoVec[(int)VampireAnim::CrGuard]->playSpeed = crGuardAnimPlaySpeed;
	}
	else
	{
		animInfoVec[(int)VampireAnim::StDamage + (int)VampireAnim::Left]->playSpeed = stHitAnimPlaySpeed;
		animInfoVec[(int)VampireAnim::CrDamage + (int)VampireAnim::Left]->playSpeed = crHitAnimPlaySpeed;
		animInfoVec[(int)VampireAnim::StGuard + (int)VampireAnim::Left]->playSpeed = stGuardAnimPlaySpeed;
		animInfoVec[(int)VampireAnim::CrGuard + (int)VampireAnim::Left]->playSpeed = crGuardAnimPlaySpeed;
	}


	//
	// Guard�̏ꍇ
	//
	if ((model->param & Parameter::Back) == Parameter::Back ||
		(model->param & Parameter::Blockstun) == Parameter::Blockstun)
	{
		// �p�����[�^���K�[�h�ɐ؂�ւ���
		model->param |= Parameter::Guard;
		model->param |= Parameter::Blockstun;


		// ���ʂ�Ԃ�(Guard)
		return false;
	}
	//
	// Hit�̏ꍇ
	//
	else
	{
		// �_���[�W����
		model->hp -= _attackPresenter->model->damage;

		// hp��0�ɂȂ����ꍇ
		if (model->hp <= 0)
		{
			model->hp = 0;
			Dead();
		}

		// �A���q�b�g
		if ((model->param & Parameter::Hitstun) == Parameter::Hitstun)
		{
			if((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
				view->animator->AnimChange((int)VampireAnim::StDamage + (int)VampireAnim::Left, true);
			else
				view->animator->AnimChange((int)VampireAnim::StDamage, true);
		}
		else
			// �p�����[�^���q�b�g�ɐ؂�ւ���
			model->param |= Parameter::Hitstun;

		view->animator->blendSpeed = 0.3f;

		// ���ʂ�Ԃ�(Hit)
		return true;
	}
}


void VampirePresenter::Awake()
{
	// ���f���̃C���X�^���X���쐬
	model = std::make_unique<VampireModel>();
	// View�R���|�[�l���g���A�^�b�`����
	view = gameObject->AddComponent<VampireView>();
	// �����I�ȏ������������s��
	view->Initialize();


	// ���g��1P��2P���𔻒肷��
	if (gameObject->name == "Player_1")
	{
		model->playerId = 1;
		gameObject->tag = (int)Tag::Player_1;
	}
	if (gameObject->name == "Player_2")
	{
		model->playerId = 2;
		gameObject->tag = (int)Tag::Player_2;
	}


	//
	// ���͊֌W�̐ݒ�
	//
	{
		if (model->playerId == 1)
			model->input->AddKeyCode("move", { PAD_INPUT_DINPUT, PAD_INPUT_1, PAD_INPUT_2 }, InputType::Key_Pad1);
		else if (model->playerId == 2)
			model->input->AddKeyCode("move", { PAD_INPUT_DINPUT, PAD_INPUT_1, PAD_INPUT_2 }, InputType::Pad2);

		model->input->AddCallBack("move", [&](InputAction::CallBackContext c) {OnKeyCheck(c);});
	}

	//
	// �R���C�_�[�̏����ݒ�
	//
	{
		model->upCollider = gameObject->AddComponent<HWCapsuleCollider>();
		// �g���K�[�ɐݒ�
		model->upCollider->isTrigger = true;

		model->upColStartPos = MV1SearchFrame(view->modelHandle, "mixamorig:Neck");
		model->upColendPos = MV1SearchFrame(view->modelHandle, "mixamorig:Hips");
		model->upCollider->radius = model->upColRadius = 35.f;

		model->upCollider->UsStartPos = MV1GetFramePosition(view->modelHandle, model->upColStartPos);
		model->upCollider->UsEndPos = MV1GetFramePosition(view->modelHandle, model->upColendPos);
	}
	{
		model->lowCollider = gameObject->AddComponent<HWCapsuleCollider>();
		// �g���K�[�ɐݒ�
		model->lowCollider->isTrigger = true;

		model->lowCenterFrame = MV1SearchFrame(view->modelHandle, "mixamorig:Hips");
		model->lowCollider->radius = model->lowColRadius = 35.f;

		model->lowCollider->UsStartPos = MV1GetFramePosition(view->modelHandle, model->lowCenterFrame);
		model->lowCollider->UsEndPos = MV1GetFramePosition(view->modelHandle, model->lowCenterFrame) - VGet(0, 60, 0);
	}

	//
	// �U������p�̃I�u�W�F�N�g�̏�����
	//
	{
		// StHa
		{
			model->stHaAttack = std::make_unique<HWGameObject>("StHa");
			model->stHaAttackPresenter = model->stHaAttack->AddComponent<AttackPresenter>();
			model->stHaAttackPresenter->CollisionSet(model.get(), view->modelHandle,
				MV1SearchFrame(view->modelHandle, "mixamorig:RightHand"), MV1SearchFrame(view->modelHandle, "mixamorig:LeftHand"),
				20.f, StHaDamage, StHaHitStun, StHaGuardStun, AttackAttribute::None);

			// �e�I�u�W�F�N�g��ݒ�
			//model->stHaAttack->SetParent(gameObject, false);
			// �R���W�����͐؂��Ă���
			model->stHaAttackPresenter->CollisionDisable();

			// �U���������̃R�[���o�b�N��ݒ�
			view->stHaOccursCallback = [&] { model->stHaAttackPresenter->CollisionEnable(); };
			// �U�������I�����̃R�[���o�b�N��ݒ�
			view->stHaFinishedCallback = [&] { model->stHaAttackPresenter->CollisionDisable(); };
		}
		// StLa
		{
			model->stLaAttack = std::make_unique<HWGameObject>("StLa");
			model->stLaAttackPresenter = model->stLaAttack->AddComponent<AttackPresenter>();
			model->stLaAttackPresenter->CollisionSet(model.get(), view->modelHandle,
				MV1SearchFrame(view->modelHandle, "mixamorig:LeftHand"), MV1SearchFrame(view->modelHandle, "mixamorig:RightHand"),
				20.f, StLaDamage, StLaHitStun, StLaGuardStun, AttackAttribute::None);

			// �e�I�u�W�F�N�g��ݒ�
			//model->stLaAttack->SetParent(gameObject, false);
			// �R���W�����͐؂��Ă���
			model->stLaAttackPresenter->CollisionDisable();

			// �U���������̃R�[���o�b�N��ݒ�
			view->stLaOccursCallback = [&] { model->stLaAttackPresenter->CollisionEnable(); };
			// �U�������I�����̃R�[���o�b�N��ݒ�
			view->stLaFinishedCallback = [&] { model->stLaAttackPresenter->CollisionDisable(); };
		}
		// CrHa
		{
			model->crHaAttack = std::make_unique<HWGameObject>("CrHa");
			model->crHaAttackPresenter = model->crHaAttack->AddComponent<AttackPresenter>();
			model->crHaAttackPresenter->CollisionSet(model.get(), view->modelHandle,
				MV1SearchFrame(view->modelHandle, "mixamorig:RightFoot"), MV1SearchFrame(view->modelHandle, "mixamorig:LeftFoot"),
				20.f, CrHaDamage, CrHaHitStun, CrHaGuardStun, AttackAttribute::KnockDown);

			// �R���W�����͐؂��Ă���
			model->crHaAttackPresenter->CollisionDisable();

			// �U���������̃R�[���o�b�N��ݒ�
			view->crHaOccursCallback = [&] { model->crHaAttackPresenter->CollisionEnable(); };
			// �U�������I�����̃R�[���o�b�N��ݒ�
			view->crHaFinishedCallback = [&] { model->crHaAttackPresenter->CollisionDisable(); };
		}
		// CrLa
		{
			model->crLaAttack = std::make_unique<HWGameObject>("CrLa");
			model->crLaAttackPresenter = model->crLaAttack->AddComponent<AttackPresenter>();
			model->crLaAttackPresenter->CollisionSet(model.get(), view->modelHandle,
				MV1SearchFrame(view->modelHandle, "mixamorig:RightFoot"), MV1SearchFrame(view->modelHandle, "mixamorig:LeftFoot"),
				20.f, CrLaDamage, CrLaHitStun, CrLaGuardStun, AttackAttribute::LowAttack);

			// �R���W�����͐؂��Ă���
			model->crLaAttackPresenter->CollisionDisable();

			// �U���������̃R�[���o�b�N��ݒ�
			view->crLaOccursCallback = [&] { model->crLaAttackPresenter->CollisionEnable(); };
			// �U�������I�����̃R�[���o�b�N��ݒ�
			view->crLaFinishedCallback = [&] { model->crLaAttackPresenter->CollisionDisable(); };
		}
		// Sp1(�g����)
		{
			view->sp1OccursCallback = [&] {
				model->projectile = new HWGameObject("Sp1");
				model->projectileCp = model->projectile->AddComponent<ProjectilePresenter>();
				model->projectileCp->CollisionSet(model.get(), VampireModel::projectileEffectHandle,
					MV1GetFramePosition(view->modelHandle, MV1SearchFrame(view->modelHandle, "mixamorig:LeftHand")), 
					40, Sp1Damage, Sp1HitStun, Sp1GuardStun, 7, AttackAttribute::None);
				};
		}
		// Sp2(������)
		{
			model->sp2Attack = std::make_unique<HWGameObject>("Sp2");
			model->sp2AttackPresenter = model->sp2Attack->AddComponent<AttackPresenter>();
			model->sp2AttackPresenter->CollisionSet(model.get(), view->modelHandle,
				MV1SearchFrame(view->modelHandle, "mixamorig:RightHand"), MV1SearchFrame(view->modelHandle, "mixamorig:LeftHand"),
				50.f, Sp2Damage, Sp2HitStun, Sp2GuardStun, AttackAttribute::LowAttack);

			// �R���W�����͐؂��Ă���
			model->sp2AttackPresenter->CollisionDisable();

			// �U���������̃R�[���o�b�N��ݒ�
			view->sp2OccursCallback = [&] { model->sp2AttackPresenter->CollisionEnable(); };
			// �U�������I�����̃R�[���o�b�N��ݒ�
			view->sp2FinishedCallback = [&] { model->sp2AttackPresenter->CollisionDisable(); };
		}
	}



	// �U���A�j���[�V�����I�����ɌĂ΂��R�[���o�b�N��ݒ�
	view->attackEndCallBack = std::bind(&VampirePresenter::AttackAnimEnd, this);
	// �K�[�h�A�j���[�V�����I�����ɌĂ΂��R�[���o�b�N��ݒ�
	view->guardEndCallBack = std::bind(&VampirePresenter::GuardAnimEnd, this);
	// �q�b�g�A�j���[�V�����I�����ɌĂ΂��R�[���o�b�N��ݒ�
	view->hitEndCallBack = std::bind(&VampirePresenter::HitAnimEnd, this);
	// ���n���̃R�[���o�b�N��ݒ�
	view->landingCallBack = [&] {
		model->param &= ~Parameter::Jump;
		model->jumpPower = 0.0f;
		};

}


void VampirePresenter::Update()
{
	//if ((GameManager::param & GameParam::Game) != GameParam::Game) return;

	// ���[�g�t���[���̂y�������̈ړ��p�����[�^�𖳌��ɂ���
	{
		// ���[�U�[�s�����������
		MV1ResetFrameUserLocalMatrix(view->modelHandle, 1);

		// ���݂̃��[�g�t���[���̍s����擾����
		MATRIX LocalMatrix = MV1GetFrameLocalMatrix(view->modelHandle, 1);

		// �y�������̕��s�ړ������𖳌��ɂ���
		LocalMatrix.m[3][2] = 0.0f;
		//LocalMatrix.m[3][1] = 0.0f;
		LocalMatrix.m[3][0] = 0.0f;

		// ���[�U�[�s��Ƃ��ĕ��s�ړ������𖳌��ɂ����s������[�g�t���[���ɃZ�b�g����
		MV1SetFrameUserLocalMatrix(view->modelHandle, 1, LocalMatrix);
	}

	// ���g�̗����ʒu�����߂�
	if ((model->param & Parameter::Jump) == Parameter::Neutral)
	{
		if (transform->position.x < opponent->transform->position.x)
		{
			model->param = static_cast<Parameter>(model->param | Parameter::Facing_Right);
			transform->rotate = VGet(0, -90, 0);
		}
		else
		{
			model->param = static_cast<Parameter>(model->param & ~Parameter::Facing_Right);
			transform->rotate = VGet(0, 90, 0);
		}
	}

	// �p�����[�^���Z�b�g
	ParameterSet();

	// �OF�̃p�����[�^��Neutral������ == Neutral���p�����Ă���̂ŁA
	// �L�[���O��Neutral���v�b�V������
	if (model->keyHistory[model->keyHistory.size() - 1] == InputKey::Neutral)
		model->keyHistory.push_back(InputKey::Neutral);

	// �A�j���[�V�������Z�b�g
	AnimChange();

	// �W�����v���̏���
	Jump();

	// �ړ�����
	Move();


	// model��Update���\�b�h�𖾎��I�ɌĂяo��
	model->ExplicitUpdate();

	//
	// �R���C�_�[�̍��W���X�V
	//
	{
		model->upCollider->UsStartPos = MV1GetFramePosition(view->modelHandle, model->upColStartPos);
		model->upCollider->UsEndPos = MV1GetFramePosition(view->modelHandle, model->upColendPos);
		model->lowCollider->UsStartPos = MV1GetFramePosition(view->modelHandle, model->lowCenterFrame);
		model->lowCollider->UsEndPos = MV1GetFramePosition(view->modelHandle, model->lowCenterFrame) - VGet(0, 60, 0);
	}


#ifdef DEBUG

	Debug();

#endif // DEBUG

}


void VampirePresenter::OnTriggerStay(HWCollider& other)
{
	if (other.gameObject->tag != (int)Tag::Player_1 && other.gameObject->tag != (int)Tag::Player_2) return;
	if (other.gameObject->tag == gameObject->tag) return;


	if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		transform->velocity.x -= 1.f;
		other.transform->position.x += 1.f;
	}
	else
	{
		transform->velocity.x += 1.f;
		other.transform->position.x -= 1.f;
	}

}




void VampirePresenter::Debug()
{
	if (CheckHitKey(KEY_INPUT_A) && model->playerId == 1)
	{
		model->hp = 0;
		Dead();
	}
	if (CheckHitKey(KEY_INPUT_Z) && model->playerId == 1)
	{
		model->hp--;
	}
}

