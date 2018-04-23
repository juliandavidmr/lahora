/* main.c generated by valac 0.38.2, the Vala compiler
 * generated from main.vala, do not modify */

/* main.vala
 *
 * Copyright (C) 2018 juliandavidmr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TYPE_APPLICATION (application_get_type ())
#define APPLICATION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_APPLICATION, Application))
#define APPLICATION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_APPLICATION, ApplicationClass))
#define IS_APPLICATION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_APPLICATION))
#define IS_APPLICATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_APPLICATION))
#define APPLICATION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_APPLICATION, ApplicationClass))

typedef struct _Application Application;
typedef struct _ApplicationClass ApplicationClass;
typedef struct _ApplicationPrivate ApplicationPrivate;
enum  {
	APPLICATION_DUMMY_PROPERTY,
	APPLICATION_LAST_PROPERTY
};
static GParamSpec* application_properties[APPLICATION_LAST_PROPERTY];
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_date_time_unref0(var) ((var == NULL) ? NULL : (var = (g_date_time_unref (var), NULL)))
#define _g_source_unref0(var) ((var == NULL) ? NULL : (var = (g_source_unref (var), NULL)))
#define _g_main_loop_unref0(var) ((var == NULL) ? NULL : (var = (g_main_loop_unref (var), NULL)))

struct _Application {
	GtkWindow parent_instance;
	ApplicationPrivate * priv;
};

struct _ApplicationClass {
	GtkWindowClass parent_class;
};

struct _ApplicationPrivate {
	GtkLabel* label_date;
};


static gpointer application_parent_class = NULL;

GType application_get_type (void) G_GNUC_CONST;
#define APPLICATION_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_APPLICATION, ApplicationPrivate))
void application_setDateLabel (Application* self);
Application* application_new (void);
Application* application_construct (GType object_type);
static void _gtk_main_quit_gtk_widget_destroy (GtkWidget* _sender, gpointer self);
static gboolean __lambda4_ (Application* self);
static gboolean ___lambda4__gsource_func (gpointer self);
static void application_finalize (GObject * obj);
gint _vala_main (gchar** args, int args_length1);


void application_setDateLabel (Application* self) {
	GDateTime* dt = NULL;
	GDateTime* _tmp0_;
	GtkLabel* _tmp1_;
	gchar* _tmp2_;
	gchar* _tmp3_;
	gchar* _tmp4_;
	gchar* _tmp5_;
	gchar* _tmp6_;
	gchar* _tmp7_;
	GtkLabel* _tmp8_;
	GtkLabel* _tmp9_;
	g_return_if_fail (self != NULL);
	_tmp0_ = g_date_time_new_now_utc ();
	dt = _tmp0_;
	_tmp1_ = self->priv->label_date;
	_tmp2_ = g_date_time_format (dt, "%X");
	_tmp3_ = _tmp2_;
	_tmp4_ = g_strconcat ("<span font='22'><b>", _tmp3_, NULL);
	_tmp5_ = _tmp4_;
	_tmp6_ = g_strconcat (_tmp5_, "</b></span>", NULL);
	_tmp7_ = _tmp6_;
	gtk_label_set_text (_tmp1_, _tmp7_);
	_g_free0 (_tmp7_);
	_g_free0 (_tmp5_);
	_g_free0 (_tmp3_);
	_tmp8_ = self->priv->label_date;
	gtk_label_set_use_markup (_tmp8_, TRUE);
	_tmp9_ = self->priv->label_date;
	gtk_label_set_line_wrap (_tmp9_, TRUE);
	g_usleep ((gulong) 1000);
	_g_date_time_unref0 (dt);
}


static void _gtk_main_quit_gtk_widget_destroy (GtkWidget* _sender, gpointer self) {
	gtk_main_quit ();
}


static gboolean __lambda4_ (Application* self) {
	gboolean result = FALSE;
	FILE* _tmp0_;
	_tmp0_ = stdout;
	fprintf (_tmp0_, "Time!\n");
	application_setDateLabel (self);
	result = TRUE;
	return result;
}


static gboolean ___lambda4__gsource_func (gpointer self) {
	gboolean result;
	result = __lambda4_ ((Application*) self);
	return result;
}


Application* application_construct (GType object_type) {
	Application * self = NULL;
	GtkBox* box = NULL;
	GtkBox* _tmp0_;
	GtkLabel* _tmp1_;
	GtkLabel* _tmp2_;
	GtkLabel* _tmp3_;
	GtkLabel* _tmp4_;
	GMainLoop* loop = NULL;
	GMainLoop* _tmp5_;
	GSource* time = NULL;
	GSource* _tmp6_;
	GMainContext* _tmp7_;
	self = (Application*) g_object_new (object_type, NULL);
	gtk_window_set_title ((GtkWindow*) self, "Clock");
	g_object_set ((GtkWindow*) self, "window-position", GTK_WIN_POS_CENTER, NULL);
	g_signal_connect ((GtkWidget*) self, "destroy", (GCallback) _gtk_main_quit_gtk_widget_destroy, NULL);
	gtk_window_set_default_size ((GtkWindow*) self, 300, 30);
	_tmp0_ = (GtkBox*) gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
	g_object_ref_sink (_tmp0_);
	box = _tmp0_;
	gtk_container_add ((GtkContainer*) self, (GtkWidget*) box);
	_tmp1_ = (GtkLabel*) gtk_label_new ("");
	g_object_ref_sink (_tmp1_);
	_g_object_unref0 (self->priv->label_date);
	self->priv->label_date = _tmp1_;
	_tmp2_ = self->priv->label_date;
	gtk_label_set_use_markup (_tmp2_, TRUE);
	_tmp3_ = self->priv->label_date;
	gtk_label_set_line_wrap (_tmp3_, TRUE);
	_tmp4_ = self->priv->label_date;
	gtk_container_add ((GtkContainer*) box, (GtkWidget*) _tmp4_);
	_tmp5_ = g_main_loop_new (NULL, FALSE);
	loop = _tmp5_;
	_tmp6_ = g_timeout_source_new ((guint) 1000);
	time = _tmp6_;
	application_setDateLabel (self);
	g_source_set_callback (time, ___lambda4__gsource_func, g_object_ref (self), g_object_unref);
	_tmp7_ = g_main_loop_get_context (loop);
	g_source_attach (time, _tmp7_);
	_g_source_unref0 (time);
	_g_main_loop_unref0 (loop);
	_g_object_unref0 (box);
	return self;
}


Application* application_new (void) {
	return application_construct (TYPE_APPLICATION);
}


static void application_class_init (ApplicationClass * klass) {
	application_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (ApplicationPrivate));
	G_OBJECT_CLASS (klass)->finalize = application_finalize;
}


static void application_instance_init (Application * self) {
	self->priv = APPLICATION_GET_PRIVATE (self);
}


static void application_finalize (GObject * obj) {
	Application * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_APPLICATION, Application);
	_g_object_unref0 (self->priv->label_date);
	G_OBJECT_CLASS (application_parent_class)->finalize (obj);
}


GType application_get_type (void) {
	static volatile gsize application_type_id__volatile = 0;
	if (g_once_init_enter (&application_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (ApplicationClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) application_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (Application), 0, (GInstanceInitFunc) application_instance_init, NULL };
		GType application_type_id;
		application_type_id = g_type_register_static (gtk_window_get_type (), "Application", &g_define_type_info, 0);
		g_once_init_leave (&application_type_id__volatile, application_type_id);
	}
	return application_type_id__volatile;
}


gint _vala_main (gchar** args, int args_length1) {
	gint result = 0;
	gboolean _tmp0_;
	Application* app = NULL;
	Application* _tmp2_;
	Application* _tmp3_;
	gtk_init (&args_length1, &args);
	_tmp0_ = g_thread_supported ();
	if (!_tmp0_) {
		FILE* _tmp1_;
		_tmp1_ = stderr;
		fprintf (_tmp1_, "Cannot run without thread support.\n");
		result = 1;
		return result;
	}
	_tmp2_ = application_new ();
	g_object_ref_sink (_tmp2_);
	app = _tmp2_;
	_tmp3_ = app;
	gtk_widget_show_all ((GtkWidget*) _tmp3_);
	gtk_main ();
	result = 0;
	_g_object_unref0 (app);
	return result;
}


int main (int argc, char ** argv) {
	return _vala_main (argv, argc);
}


