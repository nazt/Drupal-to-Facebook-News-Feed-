<?php

/**
  * Settings Form
  */
function facebook_news_feed_settings_form() {
    $form['facebook_news_feed_app_id'] = array(
      '#type' => 'textfield',
      '#title' => t('App id'),
      '#description' => t('Enter your app id'),
      '#default_value' => variable_get('facebook_news_feed_app_id', 'null')
      );

    $form['facebook_news_feed_access_token'] = array(
        '#type' => 'textfield',
        '#title' => t('Unexpired token.'),
        '#description' =>  t('Enter unexpired token'),
        '#default_value' => variable_get('facebook_news_feed_access_token', 'null'),
    );

    $form['facebook_news_feed_app_secret_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Secret Key'),
        '#description' =>  t('Enter your secret key'),
        '#default_value' => variable_get('facebook_news_feed_app_secret_key', 'null'),
    );

    $form['facebook_news_feed_login_url'] = array(
        '#type' => 'textfiled',
        '#title' => t('login url'),
        '#description' => t('Enter login url and permission'),
        '#default_value' => variable_get('facebook_news_feed_login_url', 'http://'),
      );

    $form['facebook_news_feed_page_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Page ID'),
        '#description' =>  t('Enter your secret key'),
        '#default_value' => variable_get('facebook_news_feed_page_id', '153305968014537')
    );

    $form['facebook_news_feed_redirect_to_page'] = array(
        '#type' => 'textfield',
        '#title' => t('Redirect URL'),
        '#description' => 'Enter target url (After login)',
        '#default_value' => variable_get('facebook_news_feed_redirect_to_page', 'http://'),
    );

    $form['facebook_news_feed_last_redirect'] = array(
        '#type' => 'textfield',
        '#title' => t('Last Redirect URL'),
        '#description' => 'Enter target url (After login)',
        '#default_value' => variable_get('facebook_news_feed_last_redirect', 'http://'),
    );

    $form['facebook_news_feed_aid'] = array(
        '#type' => 'textfield',
        '#title' => t('Facebook AID'),
        '#description' => 'Enter facebok AID',
        '#default_value' => variable_get('facebook_news_feed_aid', ''),
    );

    $form['facebook_news_feed_uid'] = array(
        '#type' => 'textfield',
        '#title' => t('UID'),
        '#description' => 'Enter facebook UID',
        '#default_value' => variable_get('facebook_news_feed_uid', ''),
    );

  return system_settings_form($form);
}
