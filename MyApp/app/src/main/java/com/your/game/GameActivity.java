package com.your.game;

import android.os.Bundle;
import android.widget.RelativeLayout;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.initialization.InitializationStatus;
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener;

public class GameActivity extends SDLActivity {

	private static final String TAG = "GameActivity";
	private static final int MP = RelativeLayout.LayoutParams.MATCH_PARENT;
	private static final int WC = RelativeLayout.LayoutParams.WRAP_CONTENT;

	@Override
	protected void onCreate(Bundle icicle) {
		super.onCreate(icicle);

		// AdMob
		MobileAds.initialize(this, new OnInitializationCompleteListener() {
			@Override
			public void onInitializationComplete(InitializationStatus initializationStatus) {
				CustomLog.d(TAG, "onInitializationComplete()");
				showBanner();
			}
		});
	}

	private void showBanner() {
		CustomLog.d(TAG, "showBanner()");

		// Banner
		AdView mBanner = new AdView(this);
		mBanner.setLayoutParams(new RelativeLayout.LayoutParams(WC, WC));
		mBanner.setAdSize(AdSize.BANNER);
		mBanner.setAdUnitId(getResources().getString(R.string.admob_ad_unit_id_banner));
		mBanner.setAdListener(new AdListener(){
			@Override
			public void onAdLoaded(){
				CustomLog.d(TAG, "Banner:onAdLoaded()");
			}
			@Override
			public void onAdFailedToLoad(int errorCode) {
				CustomLog.d(TAG, "Banner:onAdFailedToLoad():" + errorCode);
				switch (errorCode) {
					case AdRequest.ERROR_CODE_INTERNAL_ERROR:
						CustomLog.d(TAG, "ERROR_CODE_INTERNAL_ERROR");
						break;
					case AdRequest.ERROR_CODE_INVALID_REQUEST:
						CustomLog.d(TAG, "ERROR_CODE_INVALID_REQUEST");
						break;
					case AdRequest.ERROR_CODE_NETWORK_ERROR:
						CustomLog.d(TAG, "ERROR_CODE_NETWORK_ERROR");
						break;
					case AdRequest.ERROR_CODE_NO_FILL:
						CustomLog.d(TAG, "ERROR_CODE_NO_FILL");
						break;
					default:
						break;
				}
			}
		});

		// Request
		AdRequest.Builder builder = new AdRequest.Builder();
		//builder.addTestDevice(getResources().getString(R.string.device_test));
		AdRequest mRequest = builder.build();
		mBanner.loadAd(mRequest);

		// Layout
		RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(WC, WC);
		layoutParams.addRule(RelativeLayout.CENTER_HORIZONTAL);
		layoutParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
		mLayout.addView(mBanner, layoutParams);
	}
}
