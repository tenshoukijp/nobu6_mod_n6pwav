// _6pwav_dummy.cpp : デフォルトの処理を行うエクスポート関数
//

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include "n6pwav.h"


__declspec( naked ) void WINAPI d_DllMain() { _asm{ jmp p1_DllMain } }


int IsPreviousIsVoiceWav = 0; // 直前に再生した音は、声付きものもである。(呼応関係の音は声付きもののが連続しにくくなるように調整する)


UINT listPreProgramID[7] = {0};

// 先頭から入って、最後から出る
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

int iWhitchN6PWavUse = -1; // どのN6PWAVを使うべきか。

void JudgeOfWitchN6pWaveUse() {

	UINT KAKURITSU = 6; // 普段は1/6の確率でn6pwav3に、同じく1/6の確率でn6pwav2に行くが、状況によって変化させるため。

	// 桶狭間の戦い時の、｢ドンドンの扉叩く」の音で声が出るのを封じる
	// 桶狭間イベント以外でもこの条件を満たしてしまうことはあるが、あまり問題はない。
	/*
	1	602	成功
	15	615	門叩き、桶狭間のイベント時にも利用 
	*/
	// ３つ前は、連続で、成功音であり、かつ、今回の音が門を叩く音であれば、それはイベントの桶狭間だ。
	// よって他の変な音は入れない。デフォルトに流す。
	if (listPreProgramID[0] == 1 && listPreProgramID[1] == 1 && listPreProgramID[2] == 1 && uiProgramID == 15) {
		UnshiftPreProgramID(uiProgramID);
		IsPreviousIsVoiceWav = 0;
		// MessageBox(NULL, "この条件はおそらく桶狭間", strIDDevice, MB_OK);
		iWhitchN6PWavUse = 1;
		return; // すぐにn6pwav音にジャンプ。この音源はイベント系でも問題無い構成。
	}

	// 鉄砲を撃った、撃たれたの関係の時
	/*
	10	614	鉄砲 
	29	710	大砲着弾・鉄砲打たれ時 (うわぁ～の声)
	*/
	if (listPreProgramID[0] == 10 && uiProgramID == 29) {
		// 撃った方が声を出している場合
		// MessageBox(NULL, "撃たれて｢うわぁ｣と言ってる", strIDDevice, MB_OK);

		// 撃った方が声を出しているならば、撃たれた方はかなり声を出しにくくする。
		if (IsPreviousIsVoiceWav == 1) {
			KAKURITSU = 12; // 声重なりにくいように
		}
	}

	/*
	11	611	大砲発射
	12	612	大砲ピューン
	13	613	落城・着弾 
	18	619	挑発・混乱 
	29	710	大砲着弾・鉄砲打たれ時 
	*/
	// 大砲を撃つというのが連続して発生していると(通常は鉄甲船)、大砲を撃つ側は声が出やすくなってくる。
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
			KAKURITSU = 3; // 調子のってきたモードで声出やすい。(レアのn6pwav3やn6pwav2に行きやすい)
		}
	}

		
	// 開門した場合
	/*
	15	615	門叩き、桶狭間のイベント時にも利用 
	16	616	開門 
	*/
	// 今回が扉が開いた音で、
	if (uiProgramID == 16) {

		// １つ前が門を叩いた場合
		if (listPreProgramID[0] == 15) { 
			// MessageBox(NULL, "叩いて破壊", strIDDevice, MB_OK);
			KAKURITSU = 3;

		// １つ前は扉を叩いていたのに、今回扉が開いたということは…
		} else {
			UnshiftPreProgramID(uiProgramID);
			IsPreviousIsVoiceWav = 0;
			// MessageBox(NULL, "勝手に開いた", strIDDevice, MB_OK);
			iWhitchN6PWavUse = 1;
			return; // すぐにn6pwav音にジャンプ。勝手に開いた(即ち、扉を叩いて開いたのではなく、扉を内側から開いたので声は出さない。
		}
	}

	int random = rand();

	if ( uiProgramID == 0 ) {
		UnshiftPreProgramID(uiProgramID);
		IsPreviousIsVoiceWav = 0;
		iWhitchN6PWavUse = 1;

	// 非常に希少。1/6の確率でn6pwav3へ
	} else if (random % KAKURITSU==0) {
		UnshiftPreProgramID(uiProgramID);
		IsPreviousIsVoiceWav = 1;
		iWhitchN6PWavUse = 3;

	// 非常に希少。1/6の確率でn6pwav2へ
	} else if (random % KAKURITSU==1) {
		UnshiftPreProgramID(uiProgramID);
		IsPreviousIsVoiceWav = 1;
		iWhitchN6PWavUse = 2;

	// 普通
	} else {
		UnshiftPreProgramID(uiProgramID);
		IsPreviousIsVoiceWav = 0;
		iWhitchN6PWavUse = 1;
	}
}

// LoadWaveResourceは4バイトの引数２つで呼び出されるので、これでうまく処理されるニーモニックが生成されるのでＯＫ

__declspec( naked ) void WINAPI d_LoadWaveResource(UINT _uiProgramID, UINT _uiResourceID) {
	
	// 控えておく
	uiProgramID  = _uiProgramID;   // プログラムID, 1とか2とか連番で付いてるのやつ。
	uiResourceID = _uiResourceID;  // リソースID, 601からスタートするやつ。

	// スタックにためておく
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

			// n6pwav1へジャンプ。nakedでスタックも汚してないのでそのまま引き継がれる。
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

			// n6pwav2へジャンプ。nakedでスタックも汚してないのでそのまま引き継がれる。
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

			// n6pwav3へジャンプ。nakedでスタックも汚してないのでそのまま引き継がれる。
			jmp p3_LoadWaveResource
		}
	}

}
