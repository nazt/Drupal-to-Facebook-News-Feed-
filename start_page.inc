<?php
function start_page() {
  header('P3P: CP="NOI ADM DEV COM NAV OUR STP"');
  require_once(drupal_get_path('module', 'fb_news_feed') . '/lib/php-sdk/src/facebook.php');
  $css_path = drupal_get_path('module',  'fb_news_feed') . '/css/custom_style.css';
  $js_path  = drupal_get_path('module',  'fb_news_feed') . '/js/startup.js';

  drupal_add_css($css_path);
  drupal_add_js($js_path);

  $api_key = variable_get('facebook_news_feed_app_api_key', '');
  $secret_key = variable_get('facebook_news_feed_app_secret_key', '');
  $app_id = variable_get('facebook_news_feed_app_id', '');
  $page_id = variable_get('facebook_news_feed_page_id', '');

  $last_redirect = variable_get('facebook_news_feed_last_redirect', '');

  // Create our Application instance (replace this with your appId and secret).
  $facebook = new Facebook(array(
    'appId'  => $app_id,
    'secret' => $secret_key,
  ));

  // Get User ID
  $fb_user = $facebook->getUser();
  if ($fb_user) {
    try {
      // Proceed knowing you have a logged in user who's authenticated.
      $access_token = $facebook->getAccessToken();
      $user_id = $fb_user;
      $db_fbuid = db_result(db_query("select fbuid from {fb_news_feed_user} where fbuid = '%d'", $user_id));
      $data = array('fbuid' => $user_id, 'access_token' => $access_token, 'photo_id_posted' => null);
      // new record
      if ($db_fbuid != $user_id) {
        if ($access_token) {
          $write_result = drupal_write_record('fb_news_feed_user', $data);
          if ($write_result != FALSE) {
            drupal_set_message(t('Subscribed.'));
            drupal_add_js(array('facebook_news_feed' => array('redirectUrl' => $last_redirect)), 'setting');
          }
        }
        else {
          drupal_set_message(t('ERROR'), 'error');
        }
      }
      // Exists record.
      else {
        $write_result = drupal_write_record('fb_news_feed_user', $data, array('fbuid'));
        drupal_set_message(t('Already subscribed.'));
        drupal_add_js(array('facebook_news_feed' => array('redirectUrl' => $last_redirect)), 'setting');
      }
    }
    catch (FacebookApiException $e) {
      error_log($e);
      $fb_user = null;
    }
  }
  // If not have $fb_user go login
  else {
    $redirect_url = variable_get('facebook_news_feed_redirect_to_page', 'null');
    $loginUrl = $facebook->getLoginUrl(array('scope' => 'publish_stream, offline_access', 'redirect_uri' => $redirect_url));
  }

  // Always Add Settings.
  $fb_news_feed_data = array('apikey' => $api_key,
                       'appid' => $app_id,
                       'pageid' => $page_id,
                       'loginUrl' => $loginUrl,
                       'logoutUrl' => $logoutUrl,
                       'user' => $fb_user,
                       'uid' => $user->uid,
                      );
  $fb_news_feed_settings = array('facebook_news_feed' => $fb_news_feed_data);
  drupal_add_js($fb_news_feed_settings, 'setting');

  /**
   * Print out facebook tag
   */
  $output = <<<FBJS
    <div id="fb-root"></div>
    <p class='loading' id='prepare-page'></p>
FBJS;
  return $output;
}
