function render_display() {

}

window.fbAsyncInit = function() {
  FB.init({
    appId  : Drupal.settings.facebook_news_feed.appid,
    status : true, // check login status
    cookie : true, // enable cookies to allow the server to access the session
    xfbml  : true,  // parse XFBML
    oauth  : true  // parse XFBML
  });
  // run once with current status and whenever the status changes
  FB.getLoginStatus(function() {

  });
};

(function() {
  var e = document.createElement('script'); e.async = true;
  e.src = document.location.protocol
    + '//connect.facebook.net/en_US/all.js';
  // Wait document to ready
  $(function() {
    document.getElementById('fb-root').appendChild(e);
  });
}());


//Ready!
$(function() {
    (function() {
      var fsk = Drupal.settings.facebook_news_feed;
      (fsk.loginUrl != null) && (window.top.location = fsk.loginUrl);
      (fsk.redirectUrl != null) && (window.top.location = fsk.redirectUrl);
    })();
});

