
#include "Header/Common.h"

bool Fade( FadeMode fademode, unsigned int fadePower, int fadeColor, int waitTime ) {

	const int ALPHA_MAX = 255;
	const int ALPHA_MIN = 0;
	const int ALPHA_INVALID = -1;
	
	static int alpha = ALPHA_INVALID;
	static int waitTimeCount = 0;

	if ( alpha == ALPHA_INVALID ) {
		alpha = ( fademode == FadeMode::In ) ? ALPHA_MAX : ALPHA_MIN;
	}

	if ( fademode == FadeMode::In ) {
		if ( alpha == ALPHA_MAX ) {
			DrawBox ( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, fadeColor, true );
			waitTimeCount++;
			if ( waitTime > waitTimeCount ) {
				return false;
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, fadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	alpha = ( fademode == FadeMode::In ) ? alpha - fadePower : alpha + fadePower;

	if ( alpha < ALPHA_MIN || alpha > ALPHA_MAX ) {
		if ( fademode == FadeMode::Out ) {
			waitTimeCount++;
			if ( waitTime > waitTimeCount ) {
				return false;
			}
		}
		alpha = ALPHA_INVALID;
		waitTimeCount = 0;
		return true;
	}

	return false;
}

bool FadeIn(unsigned int fadePower, int fadeColor, int waitTime ) {
	return Fade ( FadeMode::In, fadePower, fadeColor, waitTime ) ? true : false;
}

bool FadeOut(unsigned int fadePower, int fadeColor, int waitTime ) {
	return Fade ( FadeMode::Out, fadePower, fadeColor, waitTime ) ? true : false;
}
