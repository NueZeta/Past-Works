#include "VampirePresenter.h"




void VampirePresenter::AnimChange()
{
	//
	// 右向きの場合
	//
	if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		//
		// 必殺技
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
		// 立ち状態
		//
		if ((model->param & Parameter::Crouching) == Parameter::Neutral)
		{
			// ガード中
			if ((model->param & Parameter::Blockstun) == Parameter::Blockstun)
				view->animator->AnimChange((int)VampireAnim::StGuard);
			// ヒット中
			else if ((model->param & Parameter::Hitstun) == Parameter::Hitstun)
				view->animator->AnimChange((int)VampireAnim::StDamage);

			// 強攻撃
			else if ((model->param & Parameter::Ha) == Parameter::Ha)
				view->animator->AnimChange((int)VampireAnim::StHa);
			// 弱攻撃
			else if ((model->param & Parameter::La) == Parameter::La)
				view->animator->AnimChange((int)VampireAnim::StLa);

			// 歩き
			else if ((model->param & Parameter::Walk) == Parameter::Walk)
				view->animator->AnimChange((int)VampireAnim::StWalk);
			// 後退
			else if ((model->param & Parameter::Back) == Parameter::Back)
				view->animator->AnimChange((int)VampireAnim::StBack);
			else
				view->animator->AnimChange((int)VampireAnim::StIdol);
		}

		//
		// しゃがみ状態
		//
		else if ((model->param & Parameter::Crouching) == Parameter::Crouching)
		{
			// ガード中
			if ((model->param & Parameter::Blockstun) == Parameter::Blockstun)
				view->animator->AnimChange((int)VampireAnim::CrGuard);
			// ヒット中
			else if ((model->param & Parameter::Hitstun) == Parameter::Hitstun)
				view->animator->AnimChange((int)VampireAnim::CrDamage);

			// 強攻撃
			else if ((model->param & Parameter::Ha) == Parameter::Ha)
				view->animator->AnimChange((int)VampireAnim::CrHa);
			// 弱攻撃
			else if ((model->param & Parameter::La) == Parameter::La)
				view->animator->AnimChange((int)VampireAnim::CrLa);
			else
				view->animator->AnimChange((int)VampireAnim::CrIdol);
		}
	}

	//
	// 左向きの場合
	//
	else
	{
		//
		// 必殺技
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
		// 立ち状態
		//
		if ((model->param & Parameter::Crouching) == Parameter::Neutral)
		{
			// ガード中
			if ((model->param & Parameter::Blockstun) == Parameter::Blockstun)
				view->animator->AnimChange((int)VampireAnim::StGuard + (int)VampireAnim::Left);
			// ガード中
			else if ((model->param & Parameter::Hitstun) == Parameter::Hitstun)
				view->animator->AnimChange((int)VampireAnim::StDamage + (int)VampireAnim::Left);

			// 強攻撃
			else if ((model->param & Parameter::Ha) == Parameter::Ha)
				view->animator->AnimChange((int)VampireAnim::StHa + (int)VampireAnim::Left);
			// 弱攻撃
			else if ((model->param & Parameter::La) == Parameter::La)
				view->animator->AnimChange((int)VampireAnim::StLa + (int)VampireAnim::Left);

			// 歩き
			else if ((model->param & Parameter::Walk) == Parameter::Walk)
				view->animator->AnimChange((int)VampireAnim::StWalk + (int)VampireAnim::Left);
			// 後退
			else if ((model->param & Parameter::Back) == Parameter::Back)
				view->animator->AnimChange((int)VampireAnim::StBack + (int)VampireAnim::Left);
			else
				view->animator->AnimChange((int)VampireAnim::StIdol + (int)VampireAnim::Left);
		}

		//
		// しゃがみ状態
		//
		else if ((model->param & Parameter::Crouching) == Parameter::Crouching)
		{
			// ガード中
			if ((model->param & Parameter::Blockstun) == Parameter::Blockstun)
				view->animator->AnimChange((int)VampireAnim::CrGuard + (int)VampireAnim::Left);
			// ガード中
			else if ((model->param & Parameter::Hitstun) == Parameter::Hitstun)
				view->animator->AnimChange((int)VampireAnim::CrDamage + (int)VampireAnim::Left);

			// 強攻撃
			else if ((model->param & Parameter::Ha) == Parameter::Ha)
				view->animator->AnimChange((int)VampireAnim::CrHa + (int)VampireAnim::Left);
			// 弱攻撃
			else if ((model->param & Parameter::La) == Parameter::La)
				view->animator->AnimChange((int)VampireAnim::CrLa + (int)VampireAnim::Left);
			else
				view->animator->AnimChange((int)VampireAnim::CrIdol + (int)VampireAnim::Left);
		}
	}
}


void VampirePresenter::ParameterSet()
{
	// キー入力がない場合は無視
	if (model->keyHistory.size() <= 0) return;

	// ジャンプ中は無視
	if ((model->param & Parameter::Jump) == Parameter::Jump)
		return;

	// ダメージモーション中、ガードモーション中は無視
	if ((model->param & Parameter::Hitstun) == Parameter::Hitstun ||
		(model->param & Parameter::Blockstun) == Parameter::Blockstun)
	{
		// 移動パラメータを解除
		model->param &= ~Parameter::Walk;
		model->param &= ~Parameter::Back;

		return;
	}


	// 最新の入力
	auto crrKey = model->keyHistory[model->keyHistory.size() - 1];

	// 現在の攻撃コマンドが入力1F目の場合のみ、パラメータにセットする
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
	// 攻撃行動時の処理
	//

	if ((model->param & Parameter::La) == Parameter::La ||
		(model->param & Parameter::Ha) == Parameter::Ha ||
		(model->param & Parameter::Special_1) == Parameter::Special_1 ||
		(model->param & Parameter::Special_2) == Parameter::Special_2)
	{
		// 移動パラメータを解除
		model->param &= ~Parameter::Walk;
		model->param &= ~Parameter::Back;

		// Hit or Guard中の場合
		if ((model->param & Parameter::Hit) == Parameter::Hit)
		{
			// Haの入力があった
			if ((model->crrInputParam & Parameter::Ha) == Parameter::Ha)
			{
				//
				// 必殺技でキャンセル
				//

				Parameter param = CommandCheck(Parameter::Ha);
				if ((param & Parameter::Special_1) == Parameter::Special_1)
					view->animator->AnimChange((int)VampireAnim::SpFireBall, true);
			}
		}

		return;
	}


	// Ha入力があった
	if ((model->crrInputParam & Parameter::Ha) == Parameter::Ha)
		model->param |= CommandCheck(Parameter::Ha);

	// La入力があった
	if ((model->crrInputParam & Parameter::La) == Parameter::La)
		model->param |= Parameter::La;

	// ↑入力があった
	if ((crrKey & InputKey::Up) == InputKey::Up)
		model->param |= Parameter::Jump;

	// ↓入力があった
	if ((crrKey & InputKey::Down) == InputKey::Down)
		model->param |= Parameter::Crouching;
	else
		model->param &= ~Parameter::Crouching;


	// ←入力があった
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

	// →入力がった
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
	// 右を向いている場合 
	//

	if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		//
		// 623コマンドのコマンドが成立しているかを検証
		//

		{
			// キー入力記録を古いものからコマンドの検証
			for (auto it = model->keyHistory.begin(); it != model->keyHistory.end(); ++it)
				// 最初のコマンド -> 6 を検出した
				if (*it == InputKey::Right)
				{
					for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
					{
						if (*it2 == InputKey::Down)
						{
							// キー入力記録を古いものからコマンドの検証
							for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
							{
								//
								// 623コマンド成立
								//
								if (*it2 == (InputKey::Right | InputKey::Down))
									return Parameter::Special_2;
							}
						}

						// 逆方向の入力を検知するとコマンドミス
						if (*it2 == InputKey::Left)
							return _param;
					}
					break;
				}
		}


		//
		// 236コマンドのコマンドが成立しているかを検証
		//

		{
			if(model->projectile == nullptr)
			{
				// キー入力記録を古いものからコマンドの検証
				for (auto it = model->keyHistory.begin(); it != model->keyHistory.end(); ++it)
					// 最初のコマンド -> 2 を検出した
					if (*it == InputKey::Down)
					{
						for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
						{
							// 236コマンド成立
							if (*it2 == InputKey::Right)
								return Parameter::Special_1;

							// 逆方向の入力を検知するとコマンドミス
							if (*it2 == InputKey::Left)
								return _param;
						}
						break;
					}
			}
		}


		//
		// 214コマンドのコマンドが成立しているかを検証
		//

		{
			// キー入力記録を古いものからコマンドの検証
			for (auto it = model->keyHistory.begin(); it != model->keyHistory.end(); ++it)
				// 最初のコマンド -> 2 を検出した
				if (*it == InputKey::Down)
				{
					for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
					{
						// 214コマンド成立
						if (*it2 == InputKey::Left)
							return _param;

						// 逆方向の入力を検知するとコマンドミス
						if (*it2 == InputKey::Right)
							return _param;
					}
					break;
				}
		}
	}

	//
	// 左を向いている場合
	//
	else if ((model->param & Parameter::Facing_Right) == Parameter::Neutral)
	{
		//
		// 421コマンドのコマンドが成立しているかを検証
		//

		{
			// キー入力記録を古いものからコマンドの検証
			for (auto it = model->keyHistory.begin(); it != model->keyHistory.end(); ++it)
				// 最初のコマンド -> 6 を検出した
				if (*it == InputKey::Left)
				{
					for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
					{
						if (*it2 == InputKey::Down)
						{
							// キー入力記録を古いものからコマンドの検証
							for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
							{
								//
								// 623コマンド成立
								//
								if (*it2 == (InputKey::Left | InputKey::Down))
									return Parameter::Special_2;
							}
						}

						// 逆方向の入力を検知するとコマンドミス
						if (*it2 == InputKey::Right)
							return _param;
					}
					break;
				}
		}


		//
		// 236コマンドのコマンドが成立しているかを検証
		//

		{
			if (model->projectile == nullptr)
			{

				// キー入力記録を古いものからコマンドの検証
				for (auto it = model->keyHistory.begin(); it != model->keyHistory.end(); ++it)
					// 最初のコマンド -> 2 を検出した
					if (*it == InputKey::Down)
					{
						for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
						{
							// 236コマンド成立
							if (*it2 == InputKey::Left)
								return Parameter::Special_1;

							// 逆方向の入力を検知するとコマンドミス
							if (*it2 == InputKey::Right)
								return _param;
						}
						break;
					}
			}
		}


		//
		// 214コマンドのコマンドが成立しているかを検証
		//

		{
			// キー入力記録を古いものからコマンドの検証
			for (auto it = model->keyHistory.begin(); it != model->keyHistory.end(); ++it)
				// 最初のコマンド -> 2 を検出した
				if (*it == InputKey::Down)
				{
					for (auto it2 = it; it2 != model->keyHistory.end(); ++it2)
					{
						//
						// 214コマンド成立
						//

						if (*it2 == InputKey::Right)
							return _param;

						// 逆方向の入力を検知するとコマンドミス
						if (*it2 == InputKey::Left)
							return _param;
					}
					break;
				}
		}
	}


	// コマンドが成立していなかった場合は、引数をそのまま返す
	return _param;
}


void VampirePresenter::OnKeyCheck(InputAction::CallBackContext& context)
{
	if ((GameManager::param & GameParam::Game) != GameParam::Game) return;

	// このフレームでの入力
	InputKey key = InputKey::Neutral;

	// コマンドを入力開始 or 入力中 の場合
	if (context.state == InputState::Started || context.state == InputState::Performed)
	{
		// 入力 -> 2
		if (context.dInput.Y > 100)
			key |= InputKey::Down;
		else
			key &= ~InputKey::Down;

		// 入力 -> 2
		if (context.dInput.Y < -100)
			key |= InputKey::Up;
		else
			key &= ~InputKey::Up;

		// 入力 -> 4
		if (context.dInput.X < -100)
			key |= InputKey::Left;
		else
			key &= ~InputKey::Left;

		// 入力 -> 6
		if (context.dInput.X > 100)
			key |= InputKey::Right;
		else
			key &= ~InputKey::Right;
	}

	for (auto it = context.key.begin(); it != context.key.end(); ++it)
	{
		// コマンドを入力開始 or 入力中 の場合
		if (it->inputState == InputState::Started || it->inputState == InputState::Performed)
		{
			// 入力 -> La
			if ((it->keyCode & PAD_INPUT_1) == PAD_INPUT_1)
				key |= InputKey::La;
			// 入力 -> Ha
			if ((it->keyCode & PAD_INPUT_2) == PAD_INPUT_2)
				key |= InputKey::Ha;
		}
		// 入力解除
		else if (it->inputState == InputState::Canceled)
		{
			// 入力 -> La
			if ((it->keyCode & PAD_INPUT_1) == PAD_INPUT_1)
				key &= ~InputKey::La;
			// 入力 -> Ha
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
	// 立ち,非ジャンプ状態のみ移動処理を行う
	if ((model->param & (Parameter::Crouching | Parameter::Jump)) == Parameter::Neutral)
	{
		//
		// 右向きの場合
		// 
		if((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
		{
			// 前歩き
			if ((model->param & Parameter::Walk) == Parameter::Walk)
				if(transform->position.x < StageModel::rightCorner)
					transform->velocity.x += WALK_SPEED;
			// 後ろ歩き
			if ((model->param & Parameter::Back) == Parameter::Back)
				if(transform->position.x > StageModel::leftCorner)
					transform->velocity.x -= BACK_SPEED;
		}
		//
		// 左向きの場合
		// 
		else
		{
			// 前歩き
			if ((model->param & Parameter::Walk) == Parameter::Walk)
				if (transform->position.x > StageModel::leftCorner)
					transform->velocity.x -= WALK_SPEED;
			// 後ろ歩き
			if ((model->param & Parameter::Back) == Parameter::Back)
				if (transform->position.x < StageModel::rightCorner)
					transform->velocity.x += BACK_SPEED;
		}
	}
}


void VampirePresenter::Jump()
{
	// ジャンプ中以外は無視
	if ((model->param & Parameter::Jump) != Parameter::Jump) return;

	// ジャンプ力が 0 の場合、新たにジャンプ力を設定する
	if (model->jumpPower == 0.0f)
	{
		model->jumpPower = 18.0f;
		// アニメーションを変更
		view->animator->AnimChange((int)VampireAnim::Jump, true);

		//
		// エフェクト再生
		//

		// Guard時のエフェクト再生
		HWGameObject* effect = new HWGameObject("HitEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/JumpEffect.efkefc", 10.f);
		effect->transform->position = transform->position;
		info->stopAction = StopAction::Destroy;
		info->Play();
		info->SetPlaySpeed(5.0f);
	}

	// 重力分の減算
	model->jumpPower -= 0.7f;

	//! 移動ベクトル
	VECTOR velocity = VGet(0, model->jumpPower, 0);

	// 前後ジャンプの場合、その分も加算
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

	// 座標を変更
	transform->position += velocity;

	// 地面に着地した
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
	// 攻撃と必殺技のパラメータをすべて解除
	//

	model->param &= ~Parameter::Ha;
	model->param &= ~Parameter::La;
	model->param &= ~Parameter::Special_1;
	model->param &= ~Parameter::Hit;


	// しゃがみ中の場合、再生終了時のデフォルトアニメーションをしゃがみに変更
	if ((model->param &= Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		if ((model->param & Parameter::Crouching) == Parameter::Crouching)
			view->animator->SetDefaultAnimId((int)VampireAnim::CrIdol);
		// それ以外は立ちアニメーションをセット
		else
			view->animator->SetDefaultAnimId((int)VampireAnim::StIdol);
	}
	else
	{
		if ((model->param & Parameter::Crouching) == Parameter::Crouching)
			view->animator->SetDefaultAnimId((int)VampireAnim::CrIdol + (int)VampireAnim::Left);
		// それ以外は立ちアニメーションをセット
		else
			view->animator->SetDefaultAnimId((int)VampireAnim::StIdol + (int)VampireAnim::Left);
	}
}


void VampirePresenter::GuardAnimEnd()
{
	//
	// ガードのパラメータをすべて解除
	//

	model->param &= ~Parameter::Guard;
	model->param &= ~Parameter::Blockstun;


	// しゃがみ中の場合、再生終了時のデフォルトアニメーションをしゃがみに変更
	if ((model->param &= Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		if ((model->param & Parameter::Crouching) == Parameter::Crouching)
			view->animator->SetDefaultAnimId((int)VampireAnim::CrIdol);
		// それ以外は立ちアニメーションをセット
		else
			view->animator->SetDefaultAnimId((int)VampireAnim::StIdol);
	}
	else
	{
		if ((model->param & Parameter::Crouching) == Parameter::Crouching)
			view->animator->SetDefaultAnimId((int)VampireAnim::CrIdol + (int)VampireAnim::Left);
		// それ以外は立ちアニメーションをセット
		else
			view->animator->SetDefaultAnimId((int)VampireAnim::StIdol + (int)VampireAnim::Left);
	}
}


void VampirePresenter::HitAnimEnd()
{
	//
	// ヒット時のパラメータをすべて解除
	//

	model->param &= ~Parameter::Hitstun;

	// しゃがみ中の場合、再生終了時のデフォルトアニメーションをしゃがみに変更
	if ((model->param &= Parameter::Facing_Right) == Parameter::Facing_Right)
	{
		if ((model->param & Parameter::Crouching) == Parameter::Crouching)
			view->animator->SetDefaultAnimId((int)VampireAnim::CrIdol);
		// それ以外は立ちアニメーションをセット
		else
			view->animator->SetDefaultAnimId((int)VampireAnim::StIdol);
	}
	else
	{
		if ((model->param & Parameter::Crouching) == Parameter::Crouching)
			view->animator->SetDefaultAnimId((int)VampireAnim::CrIdol + (int)VampireAnim::Left);
		// それ以外は立ちアニメーションをセット
		else
			view->animator->SetDefaultAnimId((int)VampireAnim::StIdol + (int)VampireAnim::Left);
	}
}


bool VampirePresenter::AttackHit(const AttackPresenter* _attackPresenter)
{
	//
	// アニメーションの再生速度を設定
	//

	//! アニメーションの配列
	auto& animInfoVec = view->animator->GetAnimInfoVec();

	//! 立ちヒット時のアニメーションの再生速度を計算
	double stHitAnimPlaySpeed = animInfoVec[(int)VampireAnim::StDamage]->totalTime / (double)_attackPresenter->model->hitStun;
	//! 屈ヒット時のアニメーションの再生速度を計算
	double crHitAnimPlaySpeed = animInfoVec[(int)VampireAnim::CrDamage]->totalTime / (double)_attackPresenter->model->hitStun;
	//! 立ちガード時のアニメーションの再生速度を計算
	double stGuardAnimPlaySpeed = animInfoVec[(int)VampireAnim::StGuard]->totalTime / (double)_attackPresenter->model->guardStun;
	//! 屈ガード時のアニメーションの再生速度を計算
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
	// Guardの場合
	//
			/*  上段  */
	if ((((model->param & Parameter::Back) == Parameter::Back || (model->param & Parameter::Blockstun) == Parameter::Blockstun) &&
			(_attackPresenter->model->attribute & AttackAttribute::LowAttack | AttackAttribute::OverheadAttack) == AttackAttribute::None) || 
			/*  下段  */
		(((model->param & Parameter::Back) == Parameter::Back || (model->param & Parameter::Blockstun) == Parameter::Blockstun) &&
			((_attackPresenter->model->attribute & AttackAttribute::LowAttack) == AttackAttribute::LowAttack) && (model->param & Parameter::Crouching) == Parameter::Crouching) ||
			/*  中段  */
		(((model->param & Parameter::Back) == Parameter::Back || (model->param & Parameter::Blockstun) == Parameter::Blockstun) &&
			((_attackPresenter->model->attribute & AttackAttribute::OverheadAttack) == AttackAttribute::OverheadAttack) && (model->param & Parameter::Crouching) == Parameter::Neutral))
	{
		// パラメータをガードに切り替える
		model->param |= Parameter::Guard;
		model->param |= Parameter::Blockstun;

		//
		// エフェクト再生
		//

		// Guard時のエフェクト再生
		HWGameObject* effect = new HWGameObject("HitEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/HitEffect.efkefc", 10.f);
		effect->transform->position = _attackPresenter->model->attackCol->center;
		info->stopAction = StopAction::Destroy;
		info->Play();


		// 結果を返す(Guard)
		return false;
	}
	//
	// Hitの場合
	//
	else
	{
		// ダメージ処理
		model->hp -= _attackPresenter->model->damage;

		//
		// エフェクト再生
		//

		// Hit時のエフェクト再生
		HWGameObject* effect = new HWGameObject("HitEf");
		auto info = effect->AddComponent<HWEffect>("Assets/Effect/HitEffect2.efkefc", 10.f);
		effect->transform->position = _attackPresenter->model->attackCol->center;

		if((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
			effect->transform->rotate = VGet(0,90,0);
		else
			effect->transform->rotate = VGet(0,-90,0);

		info->stopAction = StopAction::Destroy;
		info->Play();


		// hpが0になった場合
		if (model->hp <= 0)
		{
			model->hp = 0;
			Dead();
		}

		// ダウン属性の攻撃の場合、ダウンパラメータを付与する
		if ((_attackPresenter->model->attribute & AttackAttribute::KnockDown) == AttackAttribute::KnockDown)
		{
			//model->param |= Parameter::Down;
			//view->animator->AnimChange((int)VampireAnim::Down, true);
		}

		// 連続ヒット
		if((model->param & Parameter::Hitstun) == Parameter::Hitstun)
		{
			if ((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
				view->animator->AnimChange((int)VampireAnim::StDamage + (int)VampireAnim::Left, true);
			else
				view->animator->AnimChange((int)VampireAnim::StDamage, true);
		}
		else
			// パラメータをヒットに切り替える
			model->param |= Parameter::Hitstun;

		view->animator->blendSpeed = 0.3f;

		// 結果を返す(Hit)
		return true;
	}
}


bool VampirePresenter::AttackHit(const ProjectilePresenter* _attackPresenter)
{
	//
	// アニメーションの再生速度を設定
	//

	//! アニメーションの配列
	auto& animInfoVec = view->animator->GetAnimInfoVec();

	//! 立ちヒット時のアニメーションの再生速度を計算
	double stHitAnimPlaySpeed = animInfoVec[(int)VampireAnim::StDamage]->totalTime / (double)_attackPresenter->model->hitStun;
	//! 屈ヒット時のアニメーションの再生速度を計算
	double crHitAnimPlaySpeed = animInfoVec[(int)VampireAnim::CrDamage]->totalTime / (double)_attackPresenter->model->hitStun;
	//! 立ちガード時のアニメーションの再生速度を計算
	double stGuardAnimPlaySpeed = animInfoVec[(int)VampireAnim::StGuard]->totalTime / (double)_attackPresenter->model->guardStun;
	//! 屈ガード時のアニメーションの再生速度を計算
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
	// Guardの場合
	//
	if ((model->param & Parameter::Back) == Parameter::Back ||
		(model->param & Parameter::Blockstun) == Parameter::Blockstun)
	{
		// パラメータをガードに切り替える
		model->param |= Parameter::Guard;
		model->param |= Parameter::Blockstun;


		// 結果を返す(Guard)
		return false;
	}
	//
	// Hitの場合
	//
	else
	{
		// ダメージ処理
		model->hp -= _attackPresenter->model->damage;

		// hpが0になった場合
		if (model->hp <= 0)
		{
			model->hp = 0;
			Dead();
		}

		// 連続ヒット
		if ((model->param & Parameter::Hitstun) == Parameter::Hitstun)
		{
			if((model->param & Parameter::Facing_Right) == Parameter::Facing_Right)
				view->animator->AnimChange((int)VampireAnim::StDamage + (int)VampireAnim::Left, true);
			else
				view->animator->AnimChange((int)VampireAnim::StDamage, true);
		}
		else
			// パラメータをヒットに切り替える
			model->param |= Parameter::Hitstun;

		view->animator->blendSpeed = 0.3f;

		// 結果を返す(Hit)
		return true;
	}
}


void VampirePresenter::Awake()
{
	// モデルのインスタンスを作成
	model = std::make_unique<VampireModel>();
	// Viewコンポーネントをアタッチする
	view = gameObject->AddComponent<VampireView>();
	// 明示的な初期化処理を行う
	view->Initialize();


	// 自身が1Pか2Pかを判定する
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
	// 入力関係の設定
	//
	{
		if (model->playerId == 1)
			model->input->AddKeyCode("move", { PAD_INPUT_DINPUT, PAD_INPUT_1, PAD_INPUT_2 }, InputType::Key_Pad1);
		else if (model->playerId == 2)
			model->input->AddKeyCode("move", { PAD_INPUT_DINPUT, PAD_INPUT_1, PAD_INPUT_2 }, InputType::Pad2);

		model->input->AddCallBack("move", [&](InputAction::CallBackContext c) {OnKeyCheck(c);});
	}

	//
	// コライダーの初期設定
	//
	{
		model->upCollider = gameObject->AddComponent<HWCapsuleCollider>();
		// トリガーに設定
		model->upCollider->isTrigger = true;

		model->upColStartPos = MV1SearchFrame(view->modelHandle, "mixamorig:Neck");
		model->upColendPos = MV1SearchFrame(view->modelHandle, "mixamorig:Hips");
		model->upCollider->radius = model->upColRadius = 35.f;

		model->upCollider->UsStartPos = MV1GetFramePosition(view->modelHandle, model->upColStartPos);
		model->upCollider->UsEndPos = MV1GetFramePosition(view->modelHandle, model->upColendPos);
	}
	{
		model->lowCollider = gameObject->AddComponent<HWCapsuleCollider>();
		// トリガーに設定
		model->lowCollider->isTrigger = true;

		model->lowCenterFrame = MV1SearchFrame(view->modelHandle, "mixamorig:Hips");
		model->lowCollider->radius = model->lowColRadius = 35.f;

		model->lowCollider->UsStartPos = MV1GetFramePosition(view->modelHandle, model->lowCenterFrame);
		model->lowCollider->UsEndPos = MV1GetFramePosition(view->modelHandle, model->lowCenterFrame) - VGet(0, 60, 0);
	}

	//
	// 攻撃判定用のオブジェクトの初期化
	//
	{
		// StHa
		{
			model->stHaAttack = std::make_unique<HWGameObject>("StHa");
			model->stHaAttackPresenter = model->stHaAttack->AddComponent<AttackPresenter>();
			model->stHaAttackPresenter->CollisionSet(model.get(), view->modelHandle,
				MV1SearchFrame(view->modelHandle, "mixamorig:RightHand"), MV1SearchFrame(view->modelHandle, "mixamorig:LeftHand"),
				20.f, StHaDamage, StHaHitStun, StHaGuardStun, AttackAttribute::None);

			// 親オブジェクトを設定
			//model->stHaAttack->SetParent(gameObject, false);
			// コリジョンは切っておく
			model->stHaAttackPresenter->CollisionDisable();

			// 攻撃発生時のコールバックを設定
			view->stHaOccursCallback = [&] { model->stHaAttackPresenter->CollisionEnable(); };
			// 攻撃発生終了時のコールバックを設定
			view->stHaFinishedCallback = [&] { model->stHaAttackPresenter->CollisionDisable(); };
		}
		// StLa
		{
			model->stLaAttack = std::make_unique<HWGameObject>("StLa");
			model->stLaAttackPresenter = model->stLaAttack->AddComponent<AttackPresenter>();
			model->stLaAttackPresenter->CollisionSet(model.get(), view->modelHandle,
				MV1SearchFrame(view->modelHandle, "mixamorig:LeftHand"), MV1SearchFrame(view->modelHandle, "mixamorig:RightHand"),
				20.f, StLaDamage, StLaHitStun, StLaGuardStun, AttackAttribute::None);

			// 親オブジェクトを設定
			//model->stLaAttack->SetParent(gameObject, false);
			// コリジョンは切っておく
			model->stLaAttackPresenter->CollisionDisable();

			// 攻撃発生時のコールバックを設定
			view->stLaOccursCallback = [&] { model->stLaAttackPresenter->CollisionEnable(); };
			// 攻撃発生終了時のコールバックを設定
			view->stLaFinishedCallback = [&] { model->stLaAttackPresenter->CollisionDisable(); };
		}
		// CrHa
		{
			model->crHaAttack = std::make_unique<HWGameObject>("CrHa");
			model->crHaAttackPresenter = model->crHaAttack->AddComponent<AttackPresenter>();
			model->crHaAttackPresenter->CollisionSet(model.get(), view->modelHandle,
				MV1SearchFrame(view->modelHandle, "mixamorig:RightFoot"), MV1SearchFrame(view->modelHandle, "mixamorig:LeftFoot"),
				20.f, CrHaDamage, CrHaHitStun, CrHaGuardStun, AttackAttribute::KnockDown);

			// コリジョンは切っておく
			model->crHaAttackPresenter->CollisionDisable();

			// 攻撃発生時のコールバックを設定
			view->crHaOccursCallback = [&] { model->crHaAttackPresenter->CollisionEnable(); };
			// 攻撃発生終了時のコールバックを設定
			view->crHaFinishedCallback = [&] { model->crHaAttackPresenter->CollisionDisable(); };
		}
		// CrLa
		{
			model->crLaAttack = std::make_unique<HWGameObject>("CrLa");
			model->crLaAttackPresenter = model->crLaAttack->AddComponent<AttackPresenter>();
			model->crLaAttackPresenter->CollisionSet(model.get(), view->modelHandle,
				MV1SearchFrame(view->modelHandle, "mixamorig:RightFoot"), MV1SearchFrame(view->modelHandle, "mixamorig:LeftFoot"),
				20.f, CrLaDamage, CrLaHitStun, CrLaGuardStun, AttackAttribute::LowAttack);

			// コリジョンは切っておく
			model->crLaAttackPresenter->CollisionDisable();

			// 攻撃発生時のコールバックを設定
			view->crLaOccursCallback = [&] { model->crLaAttackPresenter->CollisionEnable(); };
			// 攻撃発生終了時のコールバックを設定
			view->crLaFinishedCallback = [&] { model->crLaAttackPresenter->CollisionDisable(); };
		}
		// Sp1(波動拳)
		{
			view->sp1OccursCallback = [&] {
				model->projectile = new HWGameObject("Sp1");
				model->projectileCp = model->projectile->AddComponent<ProjectilePresenter>();
				model->projectileCp->CollisionSet(model.get(), VampireModel::projectileEffectHandle,
					MV1GetFramePosition(view->modelHandle, MV1SearchFrame(view->modelHandle, "mixamorig:LeftHand")), 
					40, Sp1Damage, Sp1HitStun, Sp1GuardStun, 7, AttackAttribute::None);
				};
		}
		// Sp2(昇竜拳)
		{
			model->sp2Attack = std::make_unique<HWGameObject>("Sp2");
			model->sp2AttackPresenter = model->sp2Attack->AddComponent<AttackPresenter>();
			model->sp2AttackPresenter->CollisionSet(model.get(), view->modelHandle,
				MV1SearchFrame(view->modelHandle, "mixamorig:RightHand"), MV1SearchFrame(view->modelHandle, "mixamorig:LeftHand"),
				50.f, Sp2Damage, Sp2HitStun, Sp2GuardStun, AttackAttribute::LowAttack);

			// コリジョンは切っておく
			model->sp2AttackPresenter->CollisionDisable();

			// 攻撃発生時のコールバックを設定
			view->sp2OccursCallback = [&] { model->sp2AttackPresenter->CollisionEnable(); };
			// 攻撃発生終了時のコールバックを設定
			view->sp2FinishedCallback = [&] { model->sp2AttackPresenter->CollisionDisable(); };
		}
	}



	// 攻撃アニメーション終了時に呼ばれるコールバックを設定
	view->attackEndCallBack = std::bind(&VampirePresenter::AttackAnimEnd, this);
	// ガードアニメーション終了時に呼ばれるコールバックを設定
	view->guardEndCallBack = std::bind(&VampirePresenter::GuardAnimEnd, this);
	// ヒットアニメーション終了時に呼ばれるコールバックを設定
	view->hitEndCallBack = std::bind(&VampirePresenter::HitAnimEnd, this);
	// 着地時のコールバックを設定
	view->landingCallBack = [&] {
		model->param &= ~Parameter::Jump;
		model->jumpPower = 0.0f;
		};

}


void VampirePresenter::Update()
{
	//if ((GameManager::param & GameParam::Game) != GameParam::Game) return;

	// ルートフレームのＺ軸方向の移動パラメータを無効にする
	{
		// ユーザー行列を解除する
		MV1ResetFrameUserLocalMatrix(view->modelHandle, 1);

		// 現在のルートフレームの行列を取得する
		MATRIX LocalMatrix = MV1GetFrameLocalMatrix(view->modelHandle, 1);

		// Ｚ軸方向の平行移動成分を無効にする
		LocalMatrix.m[3][2] = 0.0f;
		//LocalMatrix.m[3][1] = 0.0f;
		LocalMatrix.m[3][0] = 0.0f;

		// ユーザー行列として平行移動成分を無効にした行列をルートフレームにセットする
		MV1SetFrameUserLocalMatrix(view->modelHandle, 1, LocalMatrix);
	}

	// 自身の立ち位置を決める
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

	// パラメータをセット
	ParameterSet();

	// 前FのパラメータがNeutralだった == Neutralが継続しているので、
	// キーログにNeutralをプッシュする
	if (model->keyHistory[model->keyHistory.size() - 1] == InputKey::Neutral)
		model->keyHistory.push_back(InputKey::Neutral);

	// アニメーションをセット
	AnimChange();

	// ジャンプ中の処理
	Jump();

	// 移動処理
	Move();


	// modelのUpdateメソッドを明示的に呼び出す
	model->ExplicitUpdate();

	//
	// コライダーの座標を更新
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

