#include "VampireView.h"

void VampireView::Initialize()
{
	// ���f���̓ǂݍ���
	{
		modelHandle = gameObject->AddComponent<HWRenderer>("Assets/Vampire/Model/Vampire.mv1")->GetModelHandle();
	}

	// �A�j���[�V�����̓ǂݍ���
	{
		animator = gameObject->AddComponent<HWAnimator>();
		animator->blendSpeed = defaultBlendSpeed;

		//
		// �E�����̃A�j���[�V����
		//
		{

			//
			// �������
			//
			{
				// StIdol_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/St/StIdol_Right.mv1");
					info->isLoop = true;
					info->interruption = true;
					info->playSpeed = StIdleAnimSpeed;
				}
				// Jump_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/St/Jump_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = JumpAnimSpeed;
					info->SubscribeEndPlaybackCallBack([&] {animator->AnimChange((int)VampireAnim::Fall); });
				}
				// Fall_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/St/Fall_Right.mv1");
					info->isLoop = true;
					info->interruption = false;
					info->playSpeed = FallAnimSpeed;
				}
				// Landing_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/St/Landing_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = LandingAnimSpeed;
					info->SubscribeEndPlaybackCallBack([&] {if (landingCallBack) landingCallBack(); });
				}
				// Down_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/St/Down_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = DownAnimSpeed;
					info->SubscribeEndPlaybackCallBack([&] {animator->isStop = true; GameManager::param = GameParam::Result;});
				}
				// WakeUp_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/St/Down_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = WakeUpAnimSpeed;
				}
				// StWalk_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/St/StWalk_Right.mv1");
					info->isLoop = true;
					info->interruption = true;
					info->playSpeed = WalkAnimSpeed;
				}
				// StBack_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/St/StBack_Right.mv1");
					info->isLoop = true;
					info->interruption = true;
					info->playSpeed = BackAnimSpeed;
				}
				// StDamage_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/St/StDamage_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = 1.5f;
					info->SubscribeEndPlaybackCallBack([&] { 
						if (hitEndCallBack) hitEndCallBack(); 
						animator->blendSpeed = defaultBlendSpeed;
						});
				}
				// StGuard_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/St/StGuard_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = 1.0f;
					info->SubscribeEndPlaybackCallBack([&] {
						if (guardEndCallBack) guardEndCallBack();
						animator->blendSpeed = defaultBlendSpeed;
						});
				}
				// StHa_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/St/StHa_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = StHaAnimSpeed;
					// �U���I�����ɌĂ΂��R�[���o�b�N��ݒ�
					info->SubscribeEndPlaybackCallBack([&] {if (attackEndCallBack) attackEndCallBack();});
					// �U������F��ݒ�
					info->AddCallBack(27.0, [&] { if (stHaOccursCallback) stHaOccursCallback(); });
					// �U���I��F��ݒ�
					info->AddCallBack(36.0, [&] { if (stHaFinishedCallback) stHaFinishedCallback(); });
				}
				// StLa_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/St/StLa_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = StLaAnimSpeed;
					// �U���I�����ɌĂ΂��R�[���o�b�N��ݒ�
					info->SubscribeEndPlaybackCallBack([&] {if (attackEndCallBack) attackEndCallBack();});
					// �U������F��ݒ�
					info->AddCallBack(12.0, [&] { if(stLaOccursCallback) stLaOccursCallback(); });
					// �U���I��F��ݒ�
					info->AddCallBack(21.0, [&] { if(stLaFinishedCallback) stLaFinishedCallback(); });
				}
			}

			//
			// ���Ⴊ�ݏ��
			//
			{
				// CrIdol_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/Cr/CrIdol_Right.mv1");
					info->isLoop = true;
					info->interruption = true;
					info->playSpeed = CrIdolAnimSpeed;
				}
				// CrDamage_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/Cr/CrDamage_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = 0.7f;
					info->SubscribeEndPlaybackCallBack([&] {
						if (hitEndCallBack) hitEndCallBack();
						animator->blendSpeed = defaultBlendSpeed;
						});
				}
				// CrGuard_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/Cr/CrGuard_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = 1.0f;
					info->SubscribeEndPlaybackCallBack([&] {
						if (guardEndCallBack) guardEndCallBack();
						animator->blendSpeed = defaultBlendSpeed;
						});
				}
				// CrHa_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/Cr/CrHa_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = CrHaAnimSpeed;
					// �U���I�����ɌĂ΂��R�[���o�b�N��ݒ�
					info->SubscribeEndPlaybackCallBack([&] {if (attackEndCallBack) attackEndCallBack();});
					// �U������F��ݒ�
					info->AddCallBack(9.0, [&] { if (crHaOccursCallback) crHaOccursCallback(); });
					// �U���I��F��ݒ�
					info->AddCallBack(21.0, [&] { if (crHaFinishedCallback) crHaFinishedCallback(); });
				}
				// CrLa_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/Cr/CrLa_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = CrLaAnimSpeed;
					// �U���I�����ɌĂ΂��R�[���o�b�N��ݒ�
					info->SubscribeEndPlaybackCallBack([&] {if (attackEndCallBack) attackEndCallBack();});
					// �U������F��ݒ�
					info->AddCallBack(9.0, [&] { if (crLaOccursCallback) crLaOccursCallback(); });
					// �U���I��F��ݒ�
					info->AddCallBack(21.0, [&] { if (crLaFinishedCallback) crLaFinishedCallback(); });
				}

			}

			//
			// �K�E�Z
			//
			{
				// SpFireBall_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/Special/SpFireBall_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = Sp1AnimSpeed;
					// �U���I�����ɌĂ΂��R�[���o�b�N��ݒ�
					info->SubscribeEndPlaybackCallBack([&] {if (attackEndCallBack) attackEndCallBack();});
					// �U������F��ݒ�
					info->AddCallBack(30., [&] { if (sp1OccursCallback) sp1OccursCallback(); });
				}
				// SpDragonUpper_Right
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Right/Special/SpDragonUpper_Right.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = Sp2AnimSpeed;
					// �U���I�����ɌĂ΂��R�[���o�b�N��ݒ�
					info->SubscribeEndPlaybackCallBack([&] {if (attackEndCallBack) attackEndCallBack(); });
					// �U������F��ݒ�
					info->AddCallBack(12.0, [&] { if (sp2OccursCallback) sp2OccursCallback(); });
					// �U���I��F��ݒ�
					info->AddCallBack(30.0, [&] { if (sp2FinishedCallback) sp2FinishedCallback(); });
				}
			}
		}

		//
		// �������̃A�j���[�V����
		//
		{
			//
			// �������
			//
			{
				// StIdol_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/St/StIdol_Left.mv1");
					info->isLoop = true;
					info->interruption = true;
					info->playSpeed = StIdleAnimSpeed;
				}
				// Jump_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/St/Jump_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = JumpAnimSpeed;
				}
				// Fall_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/St/Fall_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = FallAnimSpeed;
				}
				// Landing_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/St/Landing_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = LandingAnimSpeed;
					info->SubscribeEndPlaybackCallBack([&] {if (landingCallBack) landingCallBack(); });
				}
				// Down_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/St/Down_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = DownAnimSpeed;
				}
				// WakeUp_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/St/Down_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = WakeUpAnimSpeed;
				}
				// StWalk_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/St/StWalk_Left.mv1");
					info->isLoop = true;
					info->interruption = true;
					info->playSpeed = WalkAnimSpeed;
				}
				// StBack_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/St/StBack_Left.mv1");
					info->isLoop = true;
					info->interruption = true;
					info->playSpeed = BackAnimSpeed;
				}
				// StDamage_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/St/StDamage_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = 1.5f;
					info->SubscribeEndPlaybackCallBack([&] {
						if (hitEndCallBack) hitEndCallBack();
						animator->blendSpeed = defaultBlendSpeed;
						});
				}
				// StGuard_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/St/StGuard_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = 1.0f;
					info->SubscribeEndPlaybackCallBack([&] {
						if (guardEndCallBack) guardEndCallBack();
						animator->blendSpeed = defaultBlendSpeed;
						});
				}
				// StHa_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/St/StHa_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = StHaAnimSpeed;
					// �U���I�����ɌĂ΂��R�[���o�b�N��ݒ�
					info->SubscribeEndPlaybackCallBack([&] {if (attackEndCallBack) attackEndCallBack();});
					// �U������F��ݒ�
					info->AddCallBack(27.0, [&] { if (stHaOccursCallback) stHaOccursCallback(); });
					// �U���I��F��ݒ�
					info->AddCallBack(36.0, [&] { if (stHaFinishedCallback) stHaFinishedCallback(); });
				}
				// StLa_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/St/StLa_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = StLaAnimSpeed;
					// �U���I�����ɌĂ΂��R�[���o�b�N��ݒ�
					info->SubscribeEndPlaybackCallBack([&] {if (attackEndCallBack) attackEndCallBack();});
					// �U������F��ݒ�
					info->AddCallBack(12.0, [&] { if (stLaOccursCallback) stLaOccursCallback(); });
					// �U���I��F��ݒ�
					info->AddCallBack(21.0, [&] { if (stLaFinishedCallback) stLaFinishedCallback(); });
				}
			}

			//
			// ���Ⴊ�ݏ��
			//
			{
				// CrIdol_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/Cr/CrIdol_Left.mv1");
					info->isLoop = true;
					info->interruption = true;
					info->playSpeed = CrIdolAnimSpeed;
				}
				// CrDamage_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/Cr/CrDamage_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = 0.7f;
					info->SubscribeEndPlaybackCallBack([&] {
						if (hitEndCallBack) hitEndCallBack();
						animator->blendSpeed = defaultBlendSpeed;
						});
				}
				// CrGuard_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/Cr/CrGuard_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = 1.0f;
					info->SubscribeEndPlaybackCallBack([&] {
						if (guardEndCallBack) guardEndCallBack();
						animator->blendSpeed = defaultBlendSpeed;
						});
				}
				// CrHa_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/Cr/CrHa_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = CrHaAnimSpeed;
					// �U���I�����ɌĂ΂��R�[���o�b�N��ݒ�
					info->SubscribeEndPlaybackCallBack([&] {if (attackEndCallBack) attackEndCallBack();});
					// �U������F��ݒ�
					info->AddCallBack(9.0, [&] { if (crHaOccursCallback) crHaOccursCallback(); });
					// �U���I��F��ݒ�
					info->AddCallBack(21.0, [&] { if (crHaFinishedCallback) crHaFinishedCallback(); });
				}
				// CrLa_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/Cr/CrLa_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = CrLaAnimSpeed;
					// �U���I�����ɌĂ΂��R�[���o�b�N��ݒ�
					info->SubscribeEndPlaybackCallBack([&] {if (attackEndCallBack) attackEndCallBack();});
					// �U������F��ݒ�
					info->AddCallBack(9.0, [&] { if (crLaOccursCallback) crLaOccursCallback(); });
					// �U���I��F��ݒ�
					info->AddCallBack(21.0, [&] { if (crLaFinishedCallback) crLaFinishedCallback(); });
				}
			}

			//
			// �K�E�Z
			//
			{
				// SpFireBall_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/Special/SpFireBall_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = Sp1AnimSpeed;
					// �U���I�����ɌĂ΂��R�[���o�b�N��ݒ�
					info->SubscribeEndPlaybackCallBack([&] {if (attackEndCallBack) attackEndCallBack();});
					// �U������F��ݒ�
					info->AddCallBack(30., [&] { if (sp1OccursCallback) sp1OccursCallback(); });
				}
				// SpDragonUpper_Left
				{
					auto info = animator->AnimLoad("Assets/Vampire/Animation/Left/Special/SpDragonUpper_Left.mv1");
					info->isLoop = false;
					info->interruption = false;
					info->playSpeed = Sp2AnimSpeed;
					// �U���I�����ɌĂ΂��R�[���o�b�N��ݒ�
					info->SubscribeEndPlaybackCallBack([&] {if (attackEndCallBack) attackEndCallBack(); });
					// �U������F��ݒ�
					info->AddCallBack(12.0, [&] { if (sp2OccursCallback) sp2OccursCallback(); });
					// �U���I��F��ݒ�
					info->AddCallBack(15.0, [&] { if (sp2FinishedCallback) sp2FinishedCallback(); });
				}
			}
		}
		animator->AnimChange(0);
	}
}