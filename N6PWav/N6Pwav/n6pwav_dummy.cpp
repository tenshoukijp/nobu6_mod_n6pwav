// _6pwav_dummy.cpp : �f�t�H���g�̏������s���G�N�X�|�[�g�֐�
//

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include "n6pwav.h"


__declspec( naked ) void WINAPI d_DllMain() { _asm{ jmp p1_DllMain } }


int IsPreviousIsVoiceWav = 0; // ���O�ɍĐ��������́A���t�����̂��ł���B(�ĉ��֌W�̉��͐��t�����̂̂��A�����ɂ����Ȃ�悤�ɒ�������)


UINT listPreProgramID[7] = {0};

// �擪��������āA�Ōォ��o��
void UnshiftPreProgramID (UINT uiNewProgramID) {
	
	listPreProgramID[6] = listPreProgramID[5];
	listPreProgramID[5] = listPreProgramID[4];
	listPreProgramID[4] = listPreProgramID[3];
	listPreProgramID[3] = listPreProgramID[2];
	listPreProgramID[2] = listPreProgramID[1];
	listPreProgramID[1] = listPreProgramID[0];
	listPreProgramID[0] = uiNewProgramID;
}



UINT uiProgramID  = -1;
UINT uiResourceID = -1;

int iWhitchN6PWavUse = -1; // �ǂ�N6PWAV���g���ׂ����B

void JudgeOfWitchN6pWaveUse() {

	UINT KAKURITSU = 6; // ���i��1/6�̊m����n6pwav3�ɁA������1/6�̊m����n6pwav2�ɍs�����A�󋵂ɂ���ĕω������邽�߁B

	// �����Ԃ̐킢���́A��h���h���̔��@���v�̉��Ő����o��̂𕕂���
	// �����ԃC�x���g�ȊO�ł����̏����𖞂����Ă��܂����Ƃ͂��邪�A���܂���͂Ȃ��B
	/*
	1	602	����
	15	615	��@���A�����Ԃ̃C�x���g���ɂ����p 
	*/
	// �R�O�́A�A���ŁA�������ł���A���A����̉������@�����ł���΁A����̓C�x���g�̉����Ԃ��B
	// ����đ��̕ςȉ��͓���Ȃ��B�f�t�H���g�ɗ����B
	if (listPreProgramID[0] == 1 && listPreProgramID[1] == 1 && listPreProgramID[2] == 1 && uiProgramID == 15) {
		UnshiftPreProgramID(uiProgramID);
		IsPreviousIsVoiceWav = 0;
		// MessageBox(NULL, "���̏����͂����炭������", strIDDevice, MB_OK);
		iWhitchN6PWavUse = 1;
		return; // ������n6pwav���ɃW�����v�B���̉����̓C�x���g�n�ł���薳���\���B
	}

	// �S�C���������A�����ꂽ�̊֌W�̎�
	/*
	10	614	�S�C 
	29	710	��C���e�E�S�C�ł��ꎞ (���킟�`�̐�)
	*/
	if (listPreProgramID[0] == 10 && uiProgramID == 29) {
		// ���������������o���Ă���ꍇ
		// MessageBox(NULL, "������Ģ���킟��ƌ����Ă�", strIDDevice, MB_OK);

		// ���������������o���Ă���Ȃ�΁A�����ꂽ���͂��Ȃ萺���o���ɂ�������B
		if (IsPreviousIsVoiceWav == 1) {
			KAKURITSU = 12; // ���d�Ȃ�ɂ����悤��
		}
	}

	/*
	11	611	��C����
	12	612	��C�s���[��
	13	613	����E���e 
	18	619	�����E���� 
	29	710	��C���e�E�S�C�ł��ꎞ 
	*/
	// ��C�����Ƃ����̂��A�����Ĕ������Ă����(�ʏ�͓S�b�D)�A��C�������͐����o�₷���Ȃ��Ă���B
	if (uiProgramID == 12) {
		// sprintf(strIDDevice2, "%02d,%02d,%02d,%02d,%02d,%02d,%02d,",preIDDeviceA1,preIDDeviceA1,preIDDeviceA2,preIDDeviceA3,preIDDeviceA4,preIDDeviceA5, preIDDeviceA6,preIDDeviceA7 );
		if (
			(listPreProgramID[0] == 11 || listPreProgramID[0] == 12 || listPreProgramID[0] == 13 || listPreProgramID[0] == 18 || listPreProgramID[0] == 29) &&
			(listPreProgramID[1] == 11 || listPreProgramID[1] == 12 || listPreProgramID[1] == 13 || listPreProgramID[1] == 18 || listPreProgramID[1] == 29) &&
			(listPreProgramID[2] == 11 || listPreProgramID[2] == 12 || listPreProgramID[2] == 13 || listPreProgramID[2] == 18 || listPreProgramID[2] == 29) &&
			(listPreProgramID[3] == 11 || listPreProgramID[3] == 12 || listPreProgramID[3] == 13 || listPreProgramID[3] == 18 || listPreProgramID[3] == 29) &&
			(listPreProgramID[4] == 11 || listPreProgramID[4] == 12 || listPreProgramID[4] == 13 || listPreProgramID[4] == 18 || listPreProgramID[4] == 29) &&
			(listPreProgramID[5] == 11 || listPreProgramID[5] == 12 || listPreProgramID[5] == 13 || listPreProgramID[5] == 18 || listPreProgramID[5] == 29) &&
			(listPreProgramID[6] == 11 || listPreProgramID[6] == 12 || listPreProgramID[6] == 13 || listPreProgramID[6] == 18 || listPreProgramID[6] == 29) ) {
			KAKURITSU = 3; // ���q�̂��Ă������[�h�Ő��o�₷���B(���A��n6pwav3��n6pwav2�ɍs���₷��)
		}
	}

		
	// �J�債���ꍇ
	/*
	15	615	��@���A�����Ԃ̃C�x���g���ɂ����p 
	16	616	�J�� 
	*/
	// ���񂪔����J�������ŁA
	if (uiProgramID == 16) {

		// �P�O�����@�����ꍇ
		if (listPreProgramID[0] == 15) { 
			// MessageBox(NULL, "�@���Ĕj��", strIDDevice, MB_OK);
			KAKURITSU = 3;

		// �P�O�͔���@���Ă����̂ɁA��������J�����Ƃ������Ƃ́c
		} else {
			UnshiftPreProgramID(uiProgramID);
			IsPreviousIsVoiceWav = 0;
			// MessageBox(NULL, "����ɊJ����", strIDDevice, MB_OK);
			iWhitchN6PWavUse = 1;
			return; // ������n6pwav���ɃW�����v�B����ɊJ����(�����A����@���ĊJ�����̂ł͂Ȃ��A�����������J�����̂Ő��͏o���Ȃ��B
		}
	}

	int random = rand();

	if ( uiProgramID == 0 ) {
		UnshiftPreProgramID(uiProgramID);
		IsPreviousIsVoiceWav = 0;
		iWhitchN6PWavUse = 1;

	// ���Ɋ󏭁B1/6�̊m����n6pwav3��
	} else if (random % KAKURITSU==0) {
		UnshiftPreProgramID(uiProgramID);
		IsPreviousIsVoiceWav = 1;
		iWhitchN6PWavUse = 3;

	// ���Ɋ󏭁B1/6�̊m����n6pwav2��
	} else if (random % KAKURITSU==1) {
		UnshiftPreProgramID(uiProgramID);
		IsPreviousIsVoiceWav = 1;
		iWhitchN6PWavUse = 2;

	// ����
	} else {
		UnshiftPreProgramID(uiProgramID);
		IsPreviousIsVoiceWav = 0;
		iWhitchN6PWavUse = 1;
	}
}

// LoadWaveResource��4�o�C�g�̈����Q�ŌĂяo�����̂ŁA����ł��܂����������j�[���j�b�N�����������̂łn�j

__declspec( naked ) void WINAPI d_LoadWaveResource(UINT _uiProgramID, UINT _uiResourceID) {
	
	// �T���Ă���
	uiProgramID  = _uiProgramID;   // �v���O����ID, 1�Ƃ�2�Ƃ��A�Ԃŕt���Ă�̂�B
	uiResourceID = _uiResourceID;  // ���\�[�XID, 601����X�^�[�g�����B

	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}
	
	JudgeOfWitchN6pWaveUse();

	if ( iWhitchN6PWavUse == 1 ) {
		__asm {

			pop edi
			pop esi
			pop ebp
			pop esp
			pop edx
			pop ecx
			pop ebx
			pop eax

			// n6pwav1�փW�����v�Bnaked�ŃX�^�b�N�������ĂȂ��̂ł��̂܂܈����p�����B
			jmp p1_LoadWaveResource
		}
	}
	if ( iWhitchN6PWavUse == 2 ) {
		__asm {

			pop edi
			pop esi
			pop ebp
			pop esp
			pop edx
			pop ecx
			pop ebx
			pop eax

			// n6pwav2�փW�����v�Bnaked�ŃX�^�b�N�������ĂȂ��̂ł��̂܂܈����p�����B
			jmp p2_LoadWaveResource
		}
	}
	if ( iWhitchN6PWavUse == 3 ) {
		__asm {

			pop edi
			pop esi
			pop ebp
			pop esp
			pop edx
			pop ecx
			pop ebx
			pop eax

			// n6pwav3�փW�����v�Bnaked�ŃX�^�b�N�������ĂȂ��̂ł��̂܂܈����p�����B
			jmp p3_LoadWaveResource
		}
	}

}
