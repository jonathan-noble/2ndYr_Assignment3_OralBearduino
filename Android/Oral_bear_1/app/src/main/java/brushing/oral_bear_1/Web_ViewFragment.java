package brushing.oral_bear_1;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

public class Web_ViewFragment extends Fragment {

    public Web_ViewFragment() {
        // Required empty public constructor
    }
    //initialise webview
    public WebView mWebView;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View rootView=inflater.inflate(R.layout.fragment_web_view,
                container, false);
        //link our web control
        mWebView = (WebView) rootView.findViewById(R.id.myWebView);


        //enable jscript
        WebSettings webSettings =mWebView.getSettings();
        webSettings.setJavaScriptEnabled(true);

// Force links and redirects to open in the WebView instead of in a browser
        mWebView.setWebViewClient(new WebViewClient());

        mWebView.loadUrl("https://google.com");
        return rootView;
    }




}