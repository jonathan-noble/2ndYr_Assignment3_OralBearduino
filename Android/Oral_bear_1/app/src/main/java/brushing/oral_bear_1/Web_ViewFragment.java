package brushing.oral_bear_1;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBarDrawerToggle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.support.v7.widget.Toolbar;

public class Web_ViewFragment extends Fragment {

    //create variable for the toolbar
    Toolbar toolbar;
    //create var for action bar
    ActionBarDrawerToggle actionBarDrawerToggle;

    public Web_ViewFragment() {
        // Required empty public constructor
    }
    //initialise webview
    public static WebView mWebView;


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