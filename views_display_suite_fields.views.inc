<?php
  /**
   * @file
   * views_display_suite_fields.views.inc
   */

/**
 * Implements hook_views_data_alter().
 */
function views_display_suite_fields_views_data_alter(&$data) {
  $ds_field = array(
    'group' => t('Display Suite Field'),
    'help' => t('Provides a custom DS field.'),
    'field' => array(
      'handler' => 'views_display_suite_fields_handler_ds_field',
    ),
  );

  foreach ($data as $name => &$item) {
    if (isset($item['table']['entity type'])) {
      $item['ds_field'] = $ds_field;
      $item['ds_field']['title'] = $item['table']['group'];
    }
  }
}