<?php

/**
 * @file: 
 */

/**
 * Implements hook_field_info().
 */
function flag_entity_field_info() {
  return array(
    'flag_entity_fields_flag' => array(
      'label' => t('Flag it'),
      'description' => t("This field stores entity flaged status"),
      'settings' => array('flagable_type' => ''),
      'instance_settings' => array(),
      'default_widget' => 'options_select',
      'default_formatter' => 'flag_entity_fields_flag',
    )
  );
}

/**
 * Implements hook_field_validate().
 */
function flag_entity_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  
}

/**
 * Implements hook_field_is_empty().
 */
function flag_entity_field_is_empty($item, $field) {
  if (empty($item['value']) && (string) $item['value'] !== '0') {
    return TRUE;
  }
  return FALSE;
}

/**
 * Implements hook_field_widget_info().
 */
function flag_entity_field_widget_info() {
  return array(
    'flag_entity_fields_flag' => array(
      'label' => t('Flag'),
      'field types' => array('flag_entity_fields_flag'),
    ),
  );
}

/**
 * Implements hook_field_settings_form().
 */
function flag_entity_field_settings_form($field, $instance, $has_data) {
  dsm($has_data, '$has_data');
  dsm($field, '$field');
  dsm($instance, '$instance');

  global $user;
  // Get proper values for 'allowed_values_function', which is a core setting.
  $flags = flag_get_flags($instance['entity_type'], $instance['bundle'], $user);
  $options = array();
  foreach ($flags as $type => $flag) {
    if ($flag->show_on_form) {
      $options += array($type => $flag->title);
    }
  }
  $form['flagable_type'] = array(
    '#type' => 'select',
    '#title' => t('Flagable type'),
    '#default_value' => '',
    '#options' => $options,
    '#required' => TRUE,
    '#description' => t('The flagable type which supplies the options for this field.'),
    '#disabled' => $has_data,
  );

  return $form;
}

/**
 * Implements hook_field_widget_form().
 * @todo: 04/08/2011 - 2h a.m: đang viết form hiển thị field flag
 */
function flag_entity_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
//  dsm($form, '$form');
//  dsm($form_state, '$form_state');
//  dsm($field, '$field');
//  dsm($instance, '$instance');
//  dsm($items, '$items');
//  dsm($delta, '$delta');
//  dsm($element, '$element');
//  global $user;
//  $flags = flag_get_flags($element['#entity_type'], $element['#bundle'], $user);
//  dsm($flags, '$flags');
//  $options = array();
//  foreach ($flags as $type => $flag) {
//    if ($flag->show_on_form) {
//      $options += array($type => $flag->title);
//    }
//  }
//  $element = $element + array(
//    '#type' => 'select',
//    '#title' => t('Flagable type'),
//    '#options' => $options,
//    '#description' => t('Flag type user able to flag.'),
//    '#default_value' => isset($items[$delta]['value']) ? $items[$delta]['value'] : NULL,
//    '#multiple' => TRUE,
//    //'#return_value' => 1,
//  );
  //dsm($element);
//  $element = $element + array(
//    '#type' => 'textfield',
//    '#default_value' => isset($items[$delta]['value']) ? $items[$delta]['value'] : NULL,
//    '#size' => $instance['widget']['settings']['size'],
//    '#maxlength' => $field['settings']['max_length'],
//    '#attributes' => array('class' => array('text-full')),
//  );
  return $element;
}

/**
 * Implements hook_field_widget_info_alter().
 */
function flag_entity_field_widget_info_alter(&$info) {
  $info['options_select']['field types'][] = 'flag_entity_fields_flag';
  $info['options_buttons']['field types'][] = 'flag_entity_fields_flag';
}

/**
 * Implements hook_options_list().
 */
function flag_entity_options_list($field) {
  $function = !empty($field['settings']['options_list_callback']) ? $field['settings']['options_list_callback'] : 'flag_entity_allowed_values';
  return $function($field);
}

/**
 * Returns the set of valid terms for a taxonomy field.
 *
 * @param $field
 *   The field definition.
 * @return
 *   The array of valid terms for this field, keyed by term id.
 */
function flag_entity_allowed_values($field) {
  dsm($field);
  $options = array();
  foreach ($field['settings'] as $tree) {
    
  }
  return $options;
}

/**
 * Implements hook_field_presave().
 */
function flag_entity_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  //dsm($items, 'item at presave');
  if ($field['type'] == 'flag_entity_fields_flag') {
    
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function flag_entity_field_formatter_info() {
  return array(
    'flag_entity_fields_flag' => array(
      'label' => t('Flag'),
      'field types' => array('flag_entity_fields_flag'),
    )
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function flag_entity_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $settings = $display['settings'];
  $links = flag_link($entity_type, $entity);
  dsm($items);
  switch ($display['type']) {
    case 'flag_entity_fields_flag':
      foreach ($links as $type => $link) {
        $element[$type] = array(
          '#theme' => 'links',
          '#links' => $links,
          '#attributes' => array('class' => array('links', 'inline', $type))
        );
      }
      break;
  }
  return $element;
}