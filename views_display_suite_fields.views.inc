<?php
  /**
   * @file
   * views_display_suite_fields.views.inc
   */

/**
 * Implements hook_views_handlers().
 */
function views_display_suite_fields_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'views_display_suite_fields'),
    ),
    'handlers' => array(
      'views_display_suite_fields_handler_ds_field' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}

/**
 * Implements hook_views_data().
 */
function views_display_suite_fields_views_data() {
  $data = array();
  // Add Example group
  $data['views_display_suite_fields']['table']['group'] = t('Display Suite');
  $data['views_display_suite_fields']['table']['join'] = array(
    // #global is a special flag which let's a table appear all the time.
    '#global' => array(),
  );
  // Add custom field
  $data['views_display_suite_fields']['ds_field'] = array(
    'title' => t('DS Field'),
    'help' => t('Provides a custom DS field.'),
    'field' => array(
      'handler' => 'views_display_suite_fields_handler_ds_field',
    ),
  );
  return $data;
}