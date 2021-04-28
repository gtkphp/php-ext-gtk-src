/*
+----------------------------------------------------------------------+
| PHP Version 7                                                        |
+----------------------------------------------------------------------+
| Copyright (c) 1997-2018 The PHP Group                                |
+----------------------------------------------------------------------+
| This source file is subject to version 3.01 of the PHP license,      |
| that is bundled with this package in the file LICENSE, and is        |
| available through the world-wide-web at the following url:           |
| http://www.php.net/license/3_01.txt                                  |
| If you did not receive a copy of the PHP license and are unable to   |
| obtain it through the world-wide-web, please send a note to          |
| license@php.net so we can mail you a copy immediately.               |
+----------------------------------------------------------------------+
| Author: No Name                                                      |
+----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_GTK_WIDGET_H
#define PHP_GTK_WIDGET_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define PHP_GTK_WIDGET(ptr)           ((php_gtk_widget*)(ptr))
#define PHP_GTK_WIDGET_CLASS          php_gtk_widget_class_entry
#define PHP_GTK_WIDGET_OFFSET         (sizeof(php_gtk_widget) - sizeof(zend_object))

#define PHP_GTK_WIDGET_TO_PHP_G_OBJECT(ptr)   PHP_GOBJECT_OBJECT(ptr)

#define ZOBJ_IS_PHP_GTK_WIDGET(obj)   ((obj)!=NULL && instanceof_function(obj->ce, php_gtk_widget_class_entry))
#define ZOBJ_TO_PHP_GTK_WIDGET(std)   PHP_GTK_WIDGET( ((void*)(std))-PHP_GTK_WIDGET_OFFSET )

#define ZVAL_IS_PHP_GTK_WIDGET(val)   ((val)!=NULL && Z_TYPE_P(val)==IS_OBJECT && ZOBJ_IS_PHP_GTK_WIDGET((val)->value.obj))
#define ZVAL_GET_PHP_GTK_WIDGET(val)  (((val)==NULL || ZVAL_IS_NULL(val)) ? NULL : ZOBJ_TO_PHP_GTK_WIDGET((val)->value.obj))

#define ZVAL_SET_PHP_GTK_WIDGET(z, o) do {  \
        if (o==NULL) {                              \
            ZVAL_NULL(z);                           \
        } else {                                    \
            zval *__z = (z);                        \
            Z_OBJ_P(__z) = &(o)->std;               \
            Z_TYPE_INFO_P(__z) = IS_OBJECT_EX;	    \
            GC_REFCOUNT(&o->std)++;                 \
        }                                           \
    } while (0)

extern zend_class_entry* php_gtk_widget_class_entry;

#define GTK_WIDGET_IS_IMPLEMENTED 0

#if GTK_WIDGET_IS_IMPLEMENTED

#define PHP_GTK_WIDGET_FE() \
    PHP_GTK_FE(gtk_widget_new,                                         arginfo_gtk_widget_new) \
    PHP_GTK_FE(gtk_widget_destroy,                                     arginfo_gtk_widget_destroy) \
    PHP_GTK_FE(gtk_widget_in_destruction,                              arginfo_gtk_widget_in_destruction) \
    PHP_GTK_FE(gtk_widget_destroyed,                                   arginfo_gtk_widget_destroyed) \
    PHP_GTK_FE(gtk_widget_unparent,                                    arginfo_gtk_widget_unparent) \
    PHP_GTK_FE(gtk_widget_show,                                        arginfo_gtk_widget_show) \
    PHP_GTK_FE(gtk_widget_show_now,                                    arginfo_gtk_widget_show_now) \
    PHP_GTK_FE(gtk_widget_hide,                                        arginfo_gtk_widget_hide) \
    PHP_GTK_FE(gtk_widget_show_all,                                    arginfo_gtk_widget_show_all) \
    PHP_GTK_FE(gtk_widget_map,                                         arginfo_gtk_widget_map) \
    PHP_GTK_FE(gtk_widget_unmap,                                       arginfo_gtk_widget_unmap) \
    PHP_GTK_FE(gtk_widget_realize,                                     arginfo_gtk_widget_realize) \
    PHP_GTK_FE(gtk_widget_unrealize,                                   arginfo_gtk_widget_unrealize) \
    PHP_GTK_FE(gtk_widget_draw,                                        arginfo_gtk_widget_draw) \
    PHP_GTK_FE(gtk_widget_queue_draw,                                  arginfo_gtk_widget_queue_draw) \
    PHP_GTK_FE(gtk_widget_queue_resize,                                arginfo_gtk_widget_queue_resize) \
    PHP_GTK_FE(gtk_widget_queue_resize_no_redraw,                      arginfo_gtk_widget_queue_resize_no_redraw) \
    PHP_GTK_FE(gtk_widget_queue_allocate,                              arginfo_gtk_widget_queue_allocate) \
    PHP_GTK_FE(gtk_widget_get_frame_clock,                             arginfo_gtk_widget_get_frame_clock) \
    PHP_GTK_FE(gtk_widget_get_scale_factor,                            arginfo_gtk_widget_get_scale_factor) \
    PHP_GTK_FE(gtk_widget_add_tick_callback,                           arginfo_gtk_widget_add_tick_callback) \
    PHP_GTK_FE(gtk_widget_remove_tick_callback,                        arginfo_gtk_widget_remove_tick_callback) \
    PHP_GTK_FE(gtk_widget_size_request,                                arginfo_gtk_widget_size_request) \
    PHP_GTK_FE(gtk_widget_get_child_requisition,                       arginfo_gtk_widget_get_child_requisition) \
    PHP_GTK_FE(gtk_widget_size_allocate,                               arginfo_gtk_widget_size_allocate) \
    PHP_GTK_FE(gtk_widget_size_allocate_with_baseline,                 arginfo_gtk_widget_size_allocate_with_baseline) \
    PHP_GTK_FE(gtk_widget_add_accelerator,                             arginfo_gtk_widget_add_accelerator) \
    PHP_GTK_FE(gtk_widget_remove_accelerator,                          arginfo_gtk_widget_remove_accelerator) \
    PHP_GTK_FE(gtk_widget_set_accel_path,                              arginfo_gtk_widget_set_accel_path) \
    PHP_GTK_FE(gtk_widget_list_accel_closures,                         arginfo_gtk_widget_list_accel_closures) \
    PHP_GTK_FE(gtk_widget_can_activate_accel,                          arginfo_gtk_widget_can_activate_accel) \
    PHP_GTK_FE(gtk_widget_event,                                       arginfo_gtk_widget_event) \
    PHP_GTK_FE(gtk_widget_activate,                                    arginfo_gtk_widget_activate) \
    PHP_GTK_FE(gtk_widget_reparent,                                    arginfo_gtk_widget_reparent) \
    PHP_GTK_FE(gtk_widget_intersect,                                   arginfo_gtk_widget_intersect) \
    PHP_GTK_FE(gtk_widget_is_focus,                                    arginfo_gtk_widget_is_focus) \
    PHP_GTK_FE(gtk_widget_grab_focus,                                  arginfo_gtk_widget_grab_focus) \
    PHP_GTK_FE(gtk_widget_grab_default,                                arginfo_gtk_widget_grab_default) \
    PHP_GTK_FE(gtk_widget_set_name,                                    arginfo_gtk_widget_set_name) \
    PHP_GTK_FE(gtk_widget_get_name,                                    arginfo_gtk_widget_get_name) \
    PHP_GTK_FE(gtk_widget_set_state,                                   arginfo_gtk_widget_set_state) \
    PHP_GTK_FE(gtk_widget_set_sensitive,                               arginfo_gtk_widget_set_sensitive) \
    PHP_GTK_FE(gtk_widget_set_parent,                                  arginfo_gtk_widget_set_parent) \
    PHP_GTK_FE(gtk_widget_set_parent_window,                           arginfo_gtk_widget_set_parent_window) \
    PHP_GTK_FE(gtk_widget_get_parent_window,                           arginfo_gtk_widget_get_parent_window) \
    PHP_GTK_FE(gtk_widget_set_events,                                  arginfo_gtk_widget_set_events) \
    PHP_GTK_FE(gtk_widget_get_events,                                  arginfo_gtk_widget_get_events) \
    PHP_GTK_FE(gtk_widget_add_events,                                  arginfo_gtk_widget_add_events) \
    PHP_GTK_FE(gtk_widget_set_device_events,                           arginfo_gtk_widget_set_device_events) \
    PHP_GTK_FE(gtk_widget_get_device_events,                           arginfo_gtk_widget_get_device_events) \
    PHP_GTK_FE(gtk_widget_add_device_events,                           arginfo_gtk_widget_add_device_events) \
    PHP_GTK_FE(gtk_widget_set_device_enabled,                          arginfo_gtk_widget_set_device_enabled) \
    PHP_GTK_FE(gtk_widget_get_device_enabled,                          arginfo_gtk_widget_get_device_enabled) \
    PHP_GTK_FE(gtk_widget_get_toplevel,                                arginfo_gtk_widget_get_toplevel) \
    PHP_GTK_FE(gtk_widget_get_ancestor,                                arginfo_gtk_widget_get_ancestor) \
    PHP_GTK_FE(gtk_widget_get_visual,                                  arginfo_gtk_widget_get_visual) \
    PHP_GTK_FE(gtk_widget_set_visual,                                  arginfo_gtk_widget_set_visual) \
    PHP_GTK_FE(gtk_widget_get_pointer,                                 arginfo_gtk_widget_get_pointer) \
    PHP_GTK_FE(gtk_widget_is_ancestor,                                 arginfo_gtk_widget_is_ancestor) \
    PHP_GTK_FE(gtk_widget_translate_coordinates,                       arginfo_gtk_widget_translate_coordinates) \
    PHP_GTK_FE(gtk_widget_hide_on_delete,                              arginfo_gtk_widget_hide_on_delete) \
    PHP_GTK_FE(gtk_widget_set_style,                                   arginfo_gtk_widget_set_style) \
    PHP_GTK_FE(gtk_widget_ensure_style,                                arginfo_gtk_widget_ensure_style) \
    PHP_GTK_FE(gtk_widget_get_style,                                   arginfo_gtk_widget_get_style) \
    PHP_GTK_FE(gtk_widget_reset_rc_styles,                             arginfo_gtk_widget_reset_rc_styles) \
    PHP_GTK_FE(gtk_widget_get_default_style,                           arginfo_gtk_widget_get_default_style) \
    PHP_GTK_FE(gtk_widget_set_direction,                               arginfo_gtk_widget_set_direction) \
    PHP_GTK_FE(gtk_widget_get_direction,                               arginfo_gtk_widget_get_direction) \
    PHP_GTK_FE(gtk_widget_set_default_direction,                       arginfo_gtk_widget_set_default_direction) \
    PHP_GTK_FE(gtk_widget_get_default_direction,                       arginfo_gtk_widget_get_default_direction) \
    PHP_GTK_FE(gtk_widget_shape_combine_region,                        arginfo_gtk_widget_shape_combine_region) \
    PHP_GTK_FE(gtk_widget_input_shape_combine_region,                  arginfo_gtk_widget_input_shape_combine_region) \
    PHP_GTK_FE(gtk_widget_path,                                        arginfo_gtk_widget_path) \
    PHP_GTK_FE(gtk_widget_class_path,                                  arginfo_gtk_widget_class_path) \
    PHP_GTK_FE(gtk_widget_get_composite_name,                          arginfo_gtk_widget_get_composite_name) \
    PHP_GTK_FE(gtk_widget_override_background_color,                   arginfo_gtk_widget_override_background_color) \
    PHP_GTK_FE(gtk_widget_override_color,                              arginfo_gtk_widget_override_color) \
    PHP_GTK_FE(gtk_widget_override_font,                               arginfo_gtk_widget_override_font) \
    PHP_GTK_FE(gtk_widget_override_symbolic_color,                     arginfo_gtk_widget_override_symbolic_color) \
    PHP_GTK_FE(gtk_widget_override_cursor,                             arginfo_gtk_widget_override_cursor) \
    PHP_GTK_FE(gtk_widget_modify_style,                                arginfo_gtk_widget_modify_style) \
    PHP_GTK_FE(gtk_widget_get_modifier_style,                          arginfo_gtk_widget_get_modifier_style) \
    PHP_GTK_FE(gtk_widget_modify_fg,                                   arginfo_gtk_widget_modify_fg) \
    PHP_GTK_FE(gtk_widget_modify_bg,                                   arginfo_gtk_widget_modify_bg) \
    PHP_GTK_FE(gtk_widget_modify_text,                                 arginfo_gtk_widget_modify_text) \
    PHP_GTK_FE(gtk_widget_modify_base,                                 arginfo_gtk_widget_modify_base) \
    PHP_GTK_FE(gtk_widget_modify_font,                                 arginfo_gtk_widget_modify_font) \
    PHP_GTK_FE(gtk_widget_modify_cursor,                               arginfo_gtk_widget_modify_cursor) \
    PHP_GTK_FE(gtk_widget_create_pango_context,                        arginfo_gtk_widget_create_pango_context) \
    PHP_GTK_FE(gtk_widget_get_pango_context,                           arginfo_gtk_widget_get_pango_context) \
    PHP_GTK_FE(gtk_widget_set_font_options,                            arginfo_gtk_widget_set_font_options) \
    PHP_GTK_FE(gtk_widget_get_font_options,                            arginfo_gtk_widget_get_font_options) \
    PHP_GTK_FE(gtk_widget_set_font_map,                                arginfo_gtk_widget_set_font_map) \
    PHP_GTK_FE(gtk_widget_get_font_map,                                arginfo_gtk_widget_get_font_map) \
    PHP_GTK_FE(gtk_widget_create_pango_layout,                         arginfo_gtk_widget_create_pango_layout) \
    PHP_GTK_FE(gtk_widget_render_icon,                                 arginfo_gtk_widget_render_icon) \
    PHP_GTK_FE(gtk_widget_render_icon_pixbuf,                          arginfo_gtk_widget_render_icon_pixbuf) \
    PHP_GTK_FE(gtk_widget_pop_composite_child,                         arginfo_gtk_widget_pop_composite_child) \
    PHP_GTK_FE(gtk_widget_push_composite_child,                        arginfo_gtk_widget_push_composite_child) \
    PHP_GTK_FE(gtk_widget_queue_draw_area,                             arginfo_gtk_widget_queue_draw_area) \
    PHP_GTK_FE(gtk_widget_queue_draw_region,                           arginfo_gtk_widget_queue_draw_region) \
    PHP_GTK_FE(gtk_widget_set_app_paintable,                           arginfo_gtk_widget_set_app_paintable) \
    PHP_GTK_FE(gtk_widget_set_double_buffered,                         arginfo_gtk_widget_set_double_buffered) \
    PHP_GTK_FE(gtk_widget_set_redraw_on_allocate,                      arginfo_gtk_widget_set_redraw_on_allocate) \
    PHP_GTK_FE(gtk_widget_set_composite_name,                          arginfo_gtk_widget_set_composite_name) \
    PHP_GTK_FE(gtk_widget_mnemonic_activate,                           arginfo_gtk_widget_mnemonic_activate) \
    PHP_GTK_FE(gtk_widget_class_install_style_property,                arginfo_gtk_widget_class_install_style_property) \
    PHP_GTK_FE(gtk_widget_class_install_style_property_parser,         arginfo_gtk_widget_class_install_style_property_parser) \
    PHP_GTK_FE(gtk_widget_class_find_style_property,                   arginfo_gtk_widget_class_find_style_property) \
    PHP_GTK_FE(gtk_widget_class_list_style_properties,                 arginfo_gtk_widget_class_list_style_properties) \
    PHP_GTK_FE(gtk_widget_region_intersect,                            arginfo_gtk_widget_region_intersect) \
    PHP_GTK_FE(gtk_widget_send_expose,                                 arginfo_gtk_widget_send_expose) \
    PHP_GTK_FE(gtk_widget_send_focus_change,                           arginfo_gtk_widget_send_focus_change) \
    PHP_GTK_FE(gtk_widget_style_get,                                   arginfo_gtk_widget_style_get) \
    PHP_GTK_FE(gtk_widget_style_get_property,                          arginfo_gtk_widget_style_get_property) \
    PHP_GTK_FE(gtk_widget_style_get_valist,                            arginfo_gtk_widget_style_get_valist) \
    PHP_GTK_FE(gtk_widget_style_attach,                                arginfo_gtk_widget_style_attach) \
    PHP_GTK_FE(gtk_widget_class_set_accessible_type,                   arginfo_gtk_widget_class_set_accessible_type) \
    PHP_GTK_FE(gtk_widget_class_set_accessible_role,                   arginfo_gtk_widget_class_set_accessible_role) \
    PHP_GTK_FE(gtk_widget_get_accessible,                              arginfo_gtk_widget_get_accessible) \
    PHP_GTK_FE(gtk_widget_child_focus,                                 arginfo_gtk_widget_child_focus) \
    PHP_GTK_FE(gtk_widget_child_notify,                                arginfo_gtk_widget_child_notify) \
    PHP_GTK_FE(gtk_widget_freeze_child_notify,                         arginfo_gtk_widget_freeze_child_notify) \
    PHP_GTK_FE(gtk_widget_get_child_visible,                           arginfo_gtk_widget_get_child_visible) \
    PHP_GTK_FE(gtk_widget_get_parent,                                  arginfo_gtk_widget_get_parent) \
    PHP_GTK_FE(gtk_widget_get_settings,                                arginfo_gtk_widget_get_settings) \
    PHP_GTK_FE(gtk_widget_get_clipboard,                               arginfo_gtk_widget_get_clipboard) \
    PHP_GTK_FE(gtk_widget_get_display,                                 arginfo_gtk_widget_get_display) \
    PHP_GTK_FE(gtk_widget_get_root_window,                             arginfo_gtk_widget_get_root_window) \
    PHP_GTK_FE(gtk_widget_get_screen,                                  arginfo_gtk_widget_get_screen) \
    PHP_GTK_FE(gtk_widget_has_screen,                                  arginfo_gtk_widget_has_screen) \
    PHP_GTK_FE(gtk_widget_get_size_request,                            arginfo_gtk_widget_get_size_request) \
    PHP_GTK_FE(gtk_widget_set_child_visible,                           arginfo_gtk_widget_set_child_visible) \
    PHP_GTK_FE(gtk_widget_set_size_request,                            arginfo_gtk_widget_set_size_request) \
    PHP_GTK_FE(gtk_widget_thaw_child_notify,                           arginfo_gtk_widget_thaw_child_notify) \
    PHP_GTK_FE(gtk_widget_set_no_show_all,                             arginfo_gtk_widget_set_no_show_all) \
    PHP_GTK_FE(gtk_widget_get_no_show_all,                             arginfo_gtk_widget_get_no_show_all) \
    PHP_GTK_FE(gtk_widget_list_mnemonic_labels,                        arginfo_gtk_widget_list_mnemonic_labels) \
    PHP_GTK_FE(gtk_widget_add_mnemonic_label,                          arginfo_gtk_widget_add_mnemonic_label) \
    PHP_GTK_FE(gtk_widget_remove_mnemonic_label,                       arginfo_gtk_widget_remove_mnemonic_label) \
    PHP_GTK_FE(gtk_widget_is_composited,                               arginfo_gtk_widget_is_composited) \
    PHP_GTK_FE(gtk_widget_error_bell,                                  arginfo_gtk_widget_error_bell) \
    PHP_GTK_FE(gtk_widget_keynav_failed,                               arginfo_gtk_widget_keynav_failed) \
    PHP_GTK_FE(gtk_widget_get_tooltip_markup,                          arginfo_gtk_widget_get_tooltip_markup) \
    PHP_GTK_FE(gtk_widget_set_tooltip_markup,                          arginfo_gtk_widget_set_tooltip_markup) \
    PHP_GTK_FE(gtk_widget_get_tooltip_text,                            arginfo_gtk_widget_get_tooltip_text) \
    PHP_GTK_FE(gtk_widget_set_tooltip_text,                            arginfo_gtk_widget_set_tooltip_text) \
    PHP_GTK_FE(gtk_widget_get_tooltip_window,                          arginfo_gtk_widget_get_tooltip_window) \
    PHP_GTK_FE(gtk_widget_set_tooltip_window,                          arginfo_gtk_widget_set_tooltip_window) \
    PHP_GTK_FE(gtk_widget_get_has_tooltip,                             arginfo_gtk_widget_get_has_tooltip) \
    PHP_GTK_FE(gtk_widget_set_has_tooltip,                             arginfo_gtk_widget_set_has_tooltip) \
    PHP_GTK_FE(gtk_widget_trigger_tooltip_query,                       arginfo_gtk_widget_trigger_tooltip_query) \
    PHP_GTK_FE(gtk_widget_get_window,                                  arginfo_gtk_widget_get_window) \
    PHP_GTK_FE(gtk_widget_register_window,                             arginfo_gtk_widget_register_window) \
    PHP_GTK_FE(gtk_widget_unregister_window,                           arginfo_gtk_widget_unregister_window) \
    PHP_GTK_FE(gtk_cairo_should_draw_window,                           arginfo_gtk_cairo_should_draw_window) \
    PHP_GTK_FE(gtk_cairo_transform_to_window,                          arginfo_gtk_cairo_transform_to_window) \
    PHP_GTK_FE(gtk_widget_get_allocated_width,                         arginfo_gtk_widget_get_allocated_width) \
    PHP_GTK_FE(gtk_widget_get_allocated_height,                        arginfo_gtk_widget_get_allocated_height) \
    PHP_GTK_FE(gtk_widget_get_allocation,                              arginfo_gtk_widget_get_allocation) \
    PHP_GTK_FE(gtk_widget_set_allocation,                              arginfo_gtk_widget_set_allocation) \
    PHP_GTK_FE(gtk_widget_get_allocated_baseline,                      arginfo_gtk_widget_get_allocated_baseline) \
    PHP_GTK_FE(gtk_widget_get_allocated_size,                          arginfo_gtk_widget_get_allocated_size) \
    PHP_GTK_FE(gtk_widget_get_clip,                                    arginfo_gtk_widget_get_clip) \
    PHP_GTK_FE(gtk_widget_set_clip,                                    arginfo_gtk_widget_set_clip) \
    PHP_GTK_FE(gtk_widget_get_app_paintable,                           arginfo_gtk_widget_get_app_paintable) \
    PHP_GTK_FE(gtk_widget_get_can_default,                             arginfo_gtk_widget_get_can_default) \
    PHP_GTK_FE(gtk_widget_set_can_default,                             arginfo_gtk_widget_set_can_default) \
    PHP_GTK_FE(gtk_widget_get_can_focus,                               arginfo_gtk_widget_get_can_focus) \
    PHP_GTK_FE(gtk_widget_set_can_focus,                               arginfo_gtk_widget_set_can_focus) \
    PHP_GTK_FE(gtk_widget_get_focus_on_click,                          arginfo_gtk_widget_get_focus_on_click) \
    PHP_GTK_FE(gtk_widget_set_focus_on_click,                          arginfo_gtk_widget_set_focus_on_click) \
    PHP_GTK_FE(gtk_widget_get_double_buffered,                         arginfo_gtk_widget_get_double_buffered) \
    PHP_GTK_FE(gtk_widget_get_has_window,                              arginfo_gtk_widget_get_has_window) \
    PHP_GTK_FE(gtk_widget_set_has_window,                              arginfo_gtk_widget_set_has_window) \
    PHP_GTK_FE(gtk_widget_get_sensitive,                               arginfo_gtk_widget_get_sensitive) \
    PHP_GTK_FE(gtk_widget_is_sensitive,                                arginfo_gtk_widget_is_sensitive) \
    PHP_GTK_FE(gtk_widget_get_state,                                   arginfo_gtk_widget_get_state) \
    PHP_GTK_FE(gtk_widget_get_visible,                                 arginfo_gtk_widget_get_visible) \
    PHP_GTK_FE(gtk_widget_is_visible,                                  arginfo_gtk_widget_is_visible) \
    PHP_GTK_FE(gtk_widget_set_visible,                                 arginfo_gtk_widget_set_visible) \
    PHP_GTK_FE(gtk_widget_set_state_flags,                             arginfo_gtk_widget_set_state_flags) \
    PHP_GTK_FE(gtk_widget_unset_state_flags,                           arginfo_gtk_widget_unset_state_flags) \
    PHP_GTK_FE(gtk_widget_get_state_flags,                             arginfo_gtk_widget_get_state_flags) \
    PHP_GTK_FE(gtk_widget_has_default,                                 arginfo_gtk_widget_has_default) \
    PHP_GTK_FE(gtk_widget_has_focus,                                   arginfo_gtk_widget_has_focus) \
    PHP_GTK_FE(gtk_widget_has_visible_focus,                           arginfo_gtk_widget_has_visible_focus) \
    PHP_GTK_FE(gtk_widget_has_grab,                                    arginfo_gtk_widget_has_grab) \
    PHP_GTK_FE(gtk_widget_has_rc_style,                                arginfo_gtk_widget_has_rc_style) \
    PHP_GTK_FE(gtk_widget_is_drawable,                                 arginfo_gtk_widget_is_drawable) \
    PHP_GTK_FE(gtk_widget_is_toplevel,                                 arginfo_gtk_widget_is_toplevel) \
    PHP_GTK_FE(gtk_widget_set_window,                                  arginfo_gtk_widget_set_window) \
    PHP_GTK_FE(gtk_widget_set_receives_default,                        arginfo_gtk_widget_set_receives_default) \
    PHP_GTK_FE(gtk_widget_get_receives_default,                        arginfo_gtk_widget_get_receives_default) \
    PHP_GTK_FE(gtk_widget_set_support_multidevice,                     arginfo_gtk_widget_set_support_multidevice) \
    PHP_GTK_FE(gtk_widget_get_support_multidevice,                     arginfo_gtk_widget_get_support_multidevice) \
    PHP_GTK_FE(gtk_widget_set_realized,                                arginfo_gtk_widget_set_realized) \
    PHP_GTK_FE(gtk_widget_get_realized,                                arginfo_gtk_widget_get_realized) \
    PHP_GTK_FE(gtk_widget_set_mapped,                                  arginfo_gtk_widget_set_mapped) \
    PHP_GTK_FE(gtk_widget_get_mapped,                                  arginfo_gtk_widget_get_mapped) \
    PHP_GTK_FE(gtk_widget_get_requisition,                             arginfo_gtk_widget_get_requisition) \
    PHP_GTK_FE(gtk_widget_device_is_shadowed,                          arginfo_gtk_widget_device_is_shadowed) \
    PHP_GTK_FE(gtk_widget_get_modifier_mask,                           arginfo_gtk_widget_get_modifier_mask) \
    PHP_GTK_FE(gtk_widget_insert_action_group,                         arginfo_gtk_widget_insert_action_group) \
    PHP_GTK_FE(gtk_widget_get_opacity,                                 arginfo_gtk_widget_get_opacity) \
    PHP_GTK_FE(gtk_widget_set_opacity,                                 arginfo_gtk_widget_set_opacity) \
    PHP_GTK_FE(gtk_widget_list_action_prefixes,                        arginfo_gtk_widget_list_action_prefixes) \
    PHP_GTK_FE(gtk_widget_get_action_group,                            arginfo_gtk_widget_get_action_group) \
    PHP_GTK_FE(gtk_widget_get_path,                                    arginfo_gtk_widget_get_path) \
    PHP_GTK_FE(gtk_widget_get_style_context,                           arginfo_gtk_widget_get_style_context) \
    PHP_GTK_FE(gtk_widget_reset_style,                                 arginfo_gtk_widget_reset_style) \
    PHP_GTK_FE(gtk_widget_class_get_css_name,                          arginfo_gtk_widget_class_get_css_name) \
    PHP_GTK_FE(gtk_widget_class_set_css_name,                          arginfo_gtk_widget_class_set_css_name) \
    PHP_GTK_FE(gtk_requisition_new,                                    arginfo_gtk_requisition_new) \
    PHP_GTK_FE(gtk_requisition_copy,                                   arginfo_gtk_requisition_copy) \
    PHP_GTK_FE(gtk_requisition_free,                                   arginfo_gtk_requisition_free) \
    PHP_GTK_FE(gtk_widget_get_preferred_height,                        arginfo_gtk_widget_get_preferred_height) \
    PHP_GTK_FE(gtk_widget_get_preferred_width,                         arginfo_gtk_widget_get_preferred_width) \
    PHP_GTK_FE(gtk_widget_get_preferred_height_for_width,              arginfo_gtk_widget_get_preferred_height_for_width) \
    PHP_GTK_FE(gtk_widget_get_preferred_width_for_height,              arginfo_gtk_widget_get_preferred_width_for_height) \
    PHP_GTK_FE(gtk_widget_get_preferred_height_and_baseline_for_width, arginfo_gtk_widget_get_preferred_height_and_baseline_for_width) \
    PHP_GTK_FE(gtk_widget_get_request_mode,                            arginfo_gtk_widget_get_request_mode) \
    PHP_GTK_FE(gtk_widget_get_preferred_size,                          arginfo_gtk_widget_get_preferred_size) \
    PHP_GTK_FE(gtk_distribute_natural_allocation,                      arginfo_gtk_distribute_natural_allocation) \
    PHP_GTK_FE(gtk_widget_get_halign,                                  arginfo_gtk_widget_get_halign) \
    PHP_GTK_FE(gtk_widget_set_halign,                                  arginfo_gtk_widget_set_halign) \
    PHP_GTK_FE(gtk_widget_get_valign,                                  arginfo_gtk_widget_get_valign) \
    PHP_GTK_FE(gtk_widget_get_valign_with_baseline,                    arginfo_gtk_widget_get_valign_with_baseline) \
    PHP_GTK_FE(gtk_widget_set_valign,                                  arginfo_gtk_widget_set_valign) \
    PHP_GTK_FE(gtk_widget_get_margin_left,                             arginfo_gtk_widget_get_margin_left) \
    PHP_GTK_FE(gtk_widget_set_margin_left,                             arginfo_gtk_widget_set_margin_left) \
    PHP_GTK_FE(gtk_widget_get_margin_right,                            arginfo_gtk_widget_get_margin_right) \
    PHP_GTK_FE(gtk_widget_set_margin_right,                            arginfo_gtk_widget_set_margin_right) \
    PHP_GTK_FE(gtk_widget_get_margin_start,                            arginfo_gtk_widget_get_margin_start) \
    PHP_GTK_FE(gtk_widget_set_margin_start,                            arginfo_gtk_widget_set_margin_start) \
    PHP_GTK_FE(gtk_widget_get_margin_end,                              arginfo_gtk_widget_get_margin_end) \
    PHP_GTK_FE(gtk_widget_set_margin_end,                              arginfo_gtk_widget_set_margin_end) \
    PHP_GTK_FE(gtk_widget_get_margin_top,                              arginfo_gtk_widget_get_margin_top) \
    PHP_GTK_FE(gtk_widget_set_margin_top,                              arginfo_gtk_widget_set_margin_top) \
    PHP_GTK_FE(gtk_widget_get_margin_bottom,                           arginfo_gtk_widget_get_margin_bottom) \
    PHP_GTK_FE(gtk_widget_set_margin_bottom,                           arginfo_gtk_widget_set_margin_bottom) \
    PHP_GTK_FE(gtk_widget_get_hexpand,                                 arginfo_gtk_widget_get_hexpand) \
    PHP_GTK_FE(gtk_widget_set_hexpand,                                 arginfo_gtk_widget_set_hexpand) \
    PHP_GTK_FE(gtk_widget_get_hexpand_set,                             arginfo_gtk_widget_get_hexpand_set) \
    PHP_GTK_FE(gtk_widget_set_hexpand_set,                             arginfo_gtk_widget_set_hexpand_set) \
    PHP_GTK_FE(gtk_widget_get_vexpand,                                 arginfo_gtk_widget_get_vexpand) \
    PHP_GTK_FE(gtk_widget_set_vexpand,                                 arginfo_gtk_widget_set_vexpand) \
    PHP_GTK_FE(gtk_widget_get_vexpand_set,                             arginfo_gtk_widget_get_vexpand_set) \
    PHP_GTK_FE(gtk_widget_set_vexpand_set,                             arginfo_gtk_widget_set_vexpand_set) \
    PHP_GTK_FE(gtk_widget_queue_compute_expand,                        arginfo_gtk_widget_queue_compute_expand) \
    PHP_GTK_FE(gtk_widget_compute_expand,                              arginfo_gtk_widget_compute_expand) \
    PHP_GTK_FE(gtk_widget_init_template,                               arginfo_gtk_widget_init_template) \
    PHP_GTK_FE(gtk_widget_class_set_template,                          arginfo_gtk_widget_class_set_template) \
    PHP_GTK_FE(gtk_widget_class_set_template_from_resource,            arginfo_gtk_widget_class_set_template_from_resource) \
    PHP_GTK_FE(gtk_widget_get_template_child,                          arginfo_gtk_widget_get_template_child) \
    PHP_GTK_FE(gtk_widget_class_bind_template_child_full,              arginfo_gtk_widget_class_bind_template_child_full) \
    PHP_GTK_FE(gtk_widget_class_bind_template_callback_full,           arginfo_gtk_widget_class_bind_template_callback_full) \
    PHP_GTK_FE(gtk_widget_class_set_connect_func,                      arginfo_gtk_widget_class_set_connect_func) \

#else

#define PHP_GTK_WIDGET_FE() \
    PHP_GTK_FE(gtk_widget_show,                                        arginfo_gtk_widget_show) \
    PHP_GTK_FE(gtk_widget_show_all,                                    arginfo_gtk_widget_show_all) \
    PHP_GTK_FE(gtk_widget_get_allocation,                              arginfo_gtk_widget_get_allocation) \
    PHP_GTK_FE(gtk_widget_get_preferred_width,                         arginfo_gtk_widget_get_preferred_width) \

#endif


#define PHP_GTK_WIDGET_MINIT_FUNCTION(container_ce, parent_ce) \
    php_gtk_widget_class_init(container_ce, parent_ce)

#define PHP_GTK_WIDGET_MSHUTDOWN_FUNCTION() { \
}

#define PHP_GTK_WIDGET_RSHUTDOWN_FUNCTION() {\
}

typedef struct _php_gtk_widget php_gtk_widget;
struct _php_gtk_widget {
    // put here members

    php_gobject_object parent_instance;
    // Keep blank
};


zend_class_entry *php_gtk_widget_class_init(zend_class_entry *container_ce, zend_class_entry *ce);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget___construct, 0, 0, 0)
ZEND_END_ARG_INFO()
PHP_METHOD(gtk_widget, __construct);

// bug on user_function g_signal_connect
//ZEND_ARG_OBJ_INFO(0, widget, GtkWidget, 0)



#if GTK_WIDGET_IS_IMPLEMENTED

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_new, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, type, GType, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, first_property_name, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_new);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_destroy, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_destroy);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_in_destruction, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_in_destruction);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_destroyed, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget_pointer, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_destroyed);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_unparent, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_unparent);
#endif

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_show, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_show);

#if GTK_WIDGET_IS_IMPLEMENTED
ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_show_now, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_show_now);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_hide, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_hide);
#endif

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_show_all, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_show_all);

#if GTK_WIDGET_IS_IMPLEMENTED
ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_map, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_map);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_unmap, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_unmap);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_realize, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_realize);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_unrealize, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_unrealize);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_draw, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_draw);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_queue_draw, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_queue_draw);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_queue_resize, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_queue_resize);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_queue_resize_no_redraw, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_queue_resize_no_redraw);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_queue_allocate, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_queue_allocate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_frame_clock, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_frame_clock);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_scale_factor, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_scale_factor);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_add_tick_callback, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, callback, GtkTickCallback, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, user_data, gpointer, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, notify, GDestroyNotify, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_add_tick_callback);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_remove_tick_callback, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, id, guint, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_remove_tick_callback);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_size_request, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, requisition, GtkRequisition, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_size_request);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_child_requisition, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, requisition, GtkRequisition, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_child_requisition);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_size_allocate, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, allocation, GtkAllocation, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_size_allocate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_size_allocate_with_baseline, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, allocation, GtkAllocation, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, baseline, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_size_allocate_with_baseline);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_add_accelerator, 0, ZEND_SEND_BY_VAL, 6)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, accel_signal, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, accel_group, GtkAccelGroup, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, accel_key, guint, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, accel_mods, GdkModifierType, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, accel_flags, GtkAccelFlags, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_add_accelerator);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_remove_accelerator, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, accel_group, GtkAccelGroup, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, accel_key, guint, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, accel_mods, GdkModifierType, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_remove_accelerator);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_accel_path, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, accel_path, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, accel_group, GtkAccelGroup, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_accel_path);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_list_accel_closures, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_list_accel_closures);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_can_activate_accel, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, signal_id, guint, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_can_activate_accel);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_event, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, event, GdkEvent, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_event);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_activate, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_activate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_reparent, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, new_parent, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_reparent);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_intersect, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, area, GdkRectangle, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, intersection, GdkRectangle, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_intersect);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_is_focus, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_is_focus);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_grab_focus, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_grab_focus);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_grab_default, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_grab_default);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_name, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, name, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_name);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_name, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_name);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_state, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, state, GtkStateType, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_state);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_sensitive, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, sensitive, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_sensitive);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_parent, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, parent, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_parent);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_parent_window, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, parent_window, GdkWindow, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_parent_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_parent_window, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_parent_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_events, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, events, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_events);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_events, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_events);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_add_events, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, events, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_add_events);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_device_events, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, GdkDevice, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, events, GdkEventMask, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_device_events);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_device_events, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, GdkDevice, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_device_events);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_add_device_events, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, GdkDevice, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, events, GdkEventMask, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_add_device_events);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_device_enabled, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, GdkDevice, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, enabled, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_device_enabled);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_device_enabled, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, GdkDevice, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_device_enabled);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_toplevel, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_toplevel);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_ancestor, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget_type, GType, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_ancestor);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_visual, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_visual);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_visual, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, visual, GdkVisual, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_visual);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_pointer, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_pointer);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_is_ancestor, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, ancestor, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_is_ancestor);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_translate_coordinates, 0, ZEND_SEND_BY_VAL, 6)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, src_widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, dest_widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, src_x, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, src_y, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dest_x, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, dest_y, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_translate_coordinates);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_hide_on_delete, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_hide_on_delete);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_style, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, style, GtkStyle, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_style);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_ensure_style, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_ensure_style);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_style, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_style);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_reset_rc_styles, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_reset_rc_styles);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_default_style, 0, ZEND_SEND_BY_VAL, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_default_style);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_direction, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, dir, GtkTextDirection, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_direction);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_direction, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_direction);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_default_direction, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, dir, GtkTextDirection, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_default_direction);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_default_direction, 0, ZEND_SEND_BY_VAL, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_default_direction);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_shape_combine_region, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_shape_combine_region);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_input_shape_combine_region, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_input_shape_combine_region);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_path, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, path_length, guint, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, path, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, path_reversed, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_path);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_path, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, path_length, guint, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, path, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, path_reversed, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_path);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_composite_name, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_composite_name);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_override_background_color, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, state, GtkStateFlags, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, color, GdkRGBA, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_override_background_color);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_override_color, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, state, GtkStateFlags, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, color, GdkRGBA, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_override_color);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_override_font, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_desc, PangoFontDescription, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_override_font);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_override_symbolic_color, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, name, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, color, GdkRGBA, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_override_symbolic_color);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_override_cursor, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cursor, GdkRGBA, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, secondary_cursor, GdkRGBA, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_override_cursor);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_modify_style, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, style, GtkRcStyle, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_modify_style);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_modifier_style, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_modifier_style);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_modify_fg, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, state, GtkStateType, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, color, GdkColor, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_modify_fg);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_modify_bg, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, state, GtkStateType, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, color, GdkColor, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_modify_bg);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_modify_text, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, state, GtkStateType, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, color, GdkColor, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_modify_text);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_modify_base, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, state, GtkStateType, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, color, GdkColor, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_modify_base);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_modify_font, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_desc, PangoFontDescription, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_modify_font);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_modify_cursor, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, primary, GdkColor, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, secondary, GdkColor, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_modify_cursor);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_create_pango_context, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_create_pango_context);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_pango_context, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_pango_context);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_font_options, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, options, cairo_font_options_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_font_options);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_font_options, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_font_options);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_font_map, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, font_map, PangoFontMap, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_font_map);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_font_map, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_font_map);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_create_pango_layout, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, text, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_create_pango_layout);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_render_icon, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, stock_id, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, size, GtkIconSize, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, detail, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_render_icon);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_render_icon_pixbuf, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, stock_id, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, size, GtkIconSize, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_render_icon_pixbuf);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_pop_composite_child, 0, ZEND_SEND_BY_VAL, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_pop_composite_child);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_push_composite_child, 0, ZEND_SEND_BY_VAL, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_push_composite_child);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_queue_draw_area, 0, ZEND_SEND_BY_VAL, 5)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, x, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, y, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_queue_draw_area);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_queue_draw_region, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_queue_draw_region);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_app_paintable, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, app_paintable, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_app_paintable);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_double_buffered, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, double_buffered, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_double_buffered);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_redraw_on_allocate, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, redraw_on_allocate, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_redraw_on_allocate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_composite_name, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, name, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_composite_name);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_mnemonic_activate, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, group_cycling, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_mnemonic_activate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_install_style_property, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, klass, GtkWidgetClass, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pspec, GParamSpec, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_install_style_property);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_install_style_property_parser, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, klass, GtkWidgetClass, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, pspec, GParamSpec, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, parser, GtkRcPropertyParser, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_install_style_property_parser);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_find_style_property, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, klass, GtkWidgetClass, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, property_name, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_find_style_property);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_list_style_properties, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, klass, GtkWidgetClass, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, n_properties, guint, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_list_style_properties);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_region_intersect, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, region, cairo_region_t, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_region_intersect);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_send_expose, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, event, GdkEvent, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_send_expose);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_send_focus_change, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, event, GdkEvent, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_send_focus_change);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_style_get, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, first_property_name, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_style_get);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_style_get_property, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, property_name, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, value, GValue, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_style_get_property);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_style_get_valist, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, first_property_name, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, var_args, va_list, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_style_get_valist);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_style_attach, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_style_attach);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_set_accessible_type, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget_class, GtkWidgetClass, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, type, GType, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_set_accessible_type);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_set_accessible_role, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget_class, GtkWidgetClass, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, role, AtkRole, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_set_accessible_role);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_accessible, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_accessible);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_child_focus, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, direction, GtkDirectionType, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_child_focus);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_child_notify, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, child_property, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_child_notify);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_freeze_child_notify, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_freeze_child_notify);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_child_visible, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_child_visible);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_parent, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_parent);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_settings, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_settings);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_clipboard, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, selection, GdkAtom, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_clipboard);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_display, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_display);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_root_window, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_root_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_screen, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_screen);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_has_screen, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_has_screen);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_size_request, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_size_request);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_child_visible, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, is_visible, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_child_visible);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_size_request, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_size_request);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_thaw_child_notify, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_thaw_child_notify);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_no_show_all, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, no_show_all, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_no_show_all);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_no_show_all, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_no_show_all);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_list_mnemonic_labels, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_list_mnemonic_labels);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_add_mnemonic_label, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, label, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_add_mnemonic_label);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_remove_mnemonic_label, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, label, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_remove_mnemonic_label);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_is_composited, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_is_composited);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_error_bell, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_error_bell);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_keynav_failed, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, direction, GtkDirectionType, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_keynav_failed);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_tooltip_markup, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_tooltip_markup);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_tooltip_markup, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, markup, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_tooltip_markup);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_tooltip_text, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_tooltip_text);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_tooltip_text, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, text, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_tooltip_text);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_tooltip_window, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_tooltip_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_tooltip_window, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, custom_window, GtkWindow, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_tooltip_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_has_tooltip, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_has_tooltip);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_has_tooltip, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, has_tooltip, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_has_tooltip);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_trigger_tooltip_query, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_trigger_tooltip_query);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_window, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_register_window, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, window, GdkWindow, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_register_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_unregister_window, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, window, GdkWindow, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_unregister_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_cairo_should_draw_window, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, window, GdkWindow, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_cairo_should_draw_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_cairo_transform_to_window, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, cr, cairo_t, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, window, GdkWindow, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_cairo_transform_to_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_allocated_width, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_allocated_width);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_allocated_height, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_allocated_height);
#endif

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_allocation, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_REF, allocation, GdkRectangle, 1)
    //ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_REF, allocation, GtkAllocation, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_allocation);

#if GTK_WIDGET_IS_IMPLEMENTED
ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_allocation, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, allocation, GtkAllocation, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_allocation);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_allocated_baseline, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_allocated_baseline);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_allocated_size, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, allocation, GtkAllocation, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, baseline, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_allocated_size);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_clip, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, clip, GtkAllocation, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_clip);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_clip, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, clip, GtkAllocation, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_clip);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_app_paintable, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_app_paintable);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_can_default, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_can_default);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_can_default, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, can_default, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_can_default);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_can_focus, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_can_focus);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_can_focus, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, can_focus, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_can_focus);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_focus_on_click, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_focus_on_click);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_focus_on_click, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, focus_on_click, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_focus_on_click);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_double_buffered, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_double_buffered);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_has_window, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_has_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_has_window, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, has_window, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_has_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_sensitive, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_sensitive);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_is_sensitive, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_is_sensitive);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_state, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_state);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_visible, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_visible);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_is_visible, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_is_visible);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_visible, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, visible, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_visible);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_state_flags, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, flags, GtkStateFlags, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, clear, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_state_flags);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_unset_state_flags, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, flags, GtkStateFlags, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_unset_state_flags);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_state_flags, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_state_flags);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_has_default, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_has_default);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_has_focus, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_has_focus);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_has_visible_focus, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_has_visible_focus);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_has_grab, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_has_grab);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_has_rc_style, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_has_rc_style);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_is_drawable, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_is_drawable);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_is_toplevel, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_is_toplevel);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_window, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, window, GdkWindow, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_window);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_receives_default, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, receives_default, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_receives_default);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_receives_default, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_receives_default);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_support_multidevice, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, support_multidevice, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_support_multidevice);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_support_multidevice, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_support_multidevice);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_realized, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, realized, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_realized);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_realized, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_realized);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_mapped, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, mapped, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_mapped);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_mapped, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_mapped);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_requisition, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, requisition, GtkRequisition, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_requisition);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_device_is_shadowed, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, device, GdkDevice, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_device_is_shadowed);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_modifier_mask, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, intent, GdkModifierIntent, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_modifier_mask);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_insert_action_group, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, name, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, group, GActionGroup, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_insert_action_group);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_opacity, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_opacity);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_opacity, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, opacity, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_opacity);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_list_action_prefixes, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_list_action_prefixes);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_action_group, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, prefix, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_action_group);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_path, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_path);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_style_context, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_style_context);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_reset_style, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_reset_style);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_get_css_name, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget_class, GtkWidgetClass, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_get_css_name);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_set_css_name, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget_class, GtkWidgetClass, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, name, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_set_css_name);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_requisition_new, 0, ZEND_SEND_BY_VAL, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_requisition_new);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_requisition_copy, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, requisition, GtkRequisition, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_requisition_copy);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_requisition_free, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, requisition, GtkRequisition, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_requisition_free);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_preferred_height, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, minimum_height, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, natural_height, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_preferred_height);
#endif

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_preferred_width, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, minimum_width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_REF, natural_width, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_preferred_width);

#if GTK_WIDGET_IS_IMPLEMENTED
ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_preferred_height_for_width, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, minimum_height, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, natural_height, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_preferred_height_for_width);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_preferred_width_for_height, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, height, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, minimum_width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, natural_width, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_preferred_width_for_height);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_preferred_height_and_baseline_for_width, 0, ZEND_SEND_BY_VAL, 6)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, minimum_height, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, natural_height, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, minimum_baseline, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, natural_baseline, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_preferred_height_and_baseline_for_width);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_request_mode, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_request_mode);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_preferred_size, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, minimum_size, GtkRequisition, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, natural_size, GtkRequisition, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_preferred_size);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_distribute_natural_allocation, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, extra_space, IS_LONG, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, n_requested_sizes, guint, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, sizes, GtkRequestedSize, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_distribute_natural_allocation);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_halign, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_halign);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_halign, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, align, GtkAlign, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_halign);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_valign, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_valign);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_valign_with_baseline, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_valign_with_baseline);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_valign, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, align, GtkAlign, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_valign);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_margin_left, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_margin_left);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_margin_left, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, margin, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_margin_left);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_margin_right, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_margin_right);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_margin_right, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, margin, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_margin_right);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_margin_start, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_margin_start);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_margin_start, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, margin, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_margin_start);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_margin_end, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_margin_end);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_margin_end, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, margin, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_margin_end);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_margin_top, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_margin_top);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_margin_top, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, margin, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_margin_top);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_margin_bottom, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_margin_bottom);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_margin_bottom, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, margin, IS_LONG, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_margin_bottom);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_hexpand, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_hexpand);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_hexpand, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, expand, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_hexpand);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_hexpand_set, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_hexpand_set);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_hexpand_set, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, set, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_hexpand_set);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_vexpand, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_vexpand);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_vexpand, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, expand, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_vexpand);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_vexpand_set, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_vexpand_set);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_set_vexpand_set, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, set, gboolean, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_set_vexpand_set);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_queue_compute_expand, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_queue_compute_expand);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_compute_expand, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, orientation, GtkOrientation, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_compute_expand);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_init_template, 0, ZEND_SEND_BY_VAL, 1)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_init_template);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_set_template, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget_class, GtkWidgetClass, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, template_bytes, GBytes, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_set_template);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_set_template_from_resource, 0, ZEND_SEND_BY_VAL, 2)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget_class, GtkWidgetClass, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, resource_name, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_set_template_from_resource);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_get_template_child, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget, GtkWidget, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget_type, GType, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, name, IS_STRING, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_get_template_child);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_bind_template_child_full, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget_class, GtkWidgetClass, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, name, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, internal_child, gboolean, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, struct_offset, gssize, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_bind_template_child_full);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_bind_template_callback_full, 0, ZEND_SEND_BY_VAL, 3)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget_class, GtkWidgetClass, 0)
    ZEND_ARG_TYPE_INFO(ZEND_SEND_BY_VAL, callback_name, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, callback_symbol, GCallback, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_bind_template_callback_full);

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget_class_set_connect_func, 0, ZEND_SEND_BY_VAL, 4)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, widget_class, GtkWidgetClass, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, connect_func, GtkBuilderConnectFunc, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, connect_data, gpointer, 0)
    ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, connect_data_destroy, GDestroyNotify, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(gtk_widget_class_set_connect_func);

#endif

#endif	/* PHP_GTK_WIDGET_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
