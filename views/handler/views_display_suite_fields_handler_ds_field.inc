<?php
/**
 * @file
 * views_display_suite_fields_handler_ds_field.inc
 */

/**
 * Provides a ds views field.
 */
class views_display_suite_fields_handler_ds_field extends views_handler_field {
  public function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);

    // Initialize the entity-type used.
    $table_data = views_fetch_data($this->view->base_table);
    $this->entity_type = $table_data['table']['entity type'];
    // Set base table and field information as used by views_plugin_row to
    // select the entity id if used with default query class.
    $info = entity_get_info($this->entity_type);
    if (!empty($info['base table']) && $info['base table'] == $this->view->base_table) {
      $this->base_table = $info['base table'];
      $this->base_field = $info['entity keys']['id'];
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['view_mode'] = array('default' => 'full');
    $options['field_name'] = array('default' => '_none');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $entity_info = entity_get_info($this->entity_type);
    $options = array();
    if (!empty($entity_info['view modes'])) {
      foreach ($entity_info['view modes'] as $mode => $settings) {
        $options[$mode] = $settings['label'];
      }
    }

    if (count($options) > 1) {
      $form['view_mode'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#title' => t('View mode'),
        '#default_value' => $this->options['view_mode'],
      );
    }
    else {
      $form['view_mode_info'] = array(
        '#type' => 'item',
        '#title' => t('View mode'),
        '#description' => t('Only one view mode is available for this entity type.'),
        '#markup' => $options ? current($options) : t('Default'),
      );
      $form['view_mode'] = array(
        '#type' => 'value',
        '#value' => $options ? key($options) : 'default',
      );
    }

    $fields = ds_get_fields($this->entity_type, FALSE);

    $options_fields = array('_none' => t('- None -'));
    foreach ($fields as $field_name => $field) {
      $options_fields[$field_name] = $field['title'];
    }

    $form['field_name'] = array(
      '#type' => 'select',
      '#title' => t('Field'),
      '#options' => $options_fields,
      '#default_value' => $this->options['field_name'],
    );

    return $form;
  }

  function query() {
    // do nothing -- to override the parent query.
  }

  function render($data) {
    $entity_id = $data->{$this->base_field};
    $entity_type = $this->entity_type;
    $view_mode = $this->options['view_mode'];
    $field_name = $this->options['field_name'];

    if ($field_name == '_none') {
      return '';
    }

    $entity = entity_load($entity_type, array($entity_id));

    $render = entity_view($entity_type, $entity, $view_mode);
    $view = current($render[$entity_type]);
    if (isset($view[$field_name])) {
      return drupal_render($view[$field_name]);
    }

    return '';
  }
}