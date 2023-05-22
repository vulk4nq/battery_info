#include <gtk/gtk.h>
#include <stdlib.h>

#define BATTERY_STATUS_FILE_PATH "/sys/class/power_supply/BAT0/status"
#define AC_ADAPTER_STATUS_FILE_PATH "/sys/class/power_supply/AC/online"
#define BATTERY_PERCENTAGE_FILE_PATH "/sys/class/power_supply/BAT0/capacity"
#define TIMER_FOR_CLOSES 1

char* get_battery_status()
{
	FILE *acpiFile;
    char buffer[128];   
    char *batteryStatus = NULL;
    
    acpiFile = fopen(BATTERY_STATUS_FILE_PATH, "r");

    if (acpiFile != NULL) {

        fgets(buffer, sizeof(buffer), acpiFile);
        batteryStatus = strdup(buffer);

        fclose(acpiFile);
    }
	return batteryStatus;
}
char* get_ac_adapter_status()
{
	FILE *acpiFile;
    char buffer[128];
    char *acAdapterStatus = NULL;

	acpiFile = fopen(AC_ADAPTER_STATUS_FILE_PATH, "r");

    if (acpiFile != NULL) {
        fgets(buffer, sizeof(buffer), acpiFile);
        acAdapterStatus = strdup(buffer);
        fclose(acpiFile);
    }
	return acAdapterStatus;
}
int get_battery_percentage()
{
	FILE *acpiFile;
    char buffer[128];
    int batteryPercentage = 0;

	acpiFile = fopen(BATTERY_PERCENTAGE_FILE_PATH, "r");

    if (acpiFile != NULL) {
        fgets(buffer, sizeof(buffer), acpiFile);
        batteryPercentage = atoi(buffer);
        fclose(acpiFile);
    }
	return batteryPercentage;
}

gboolean close_dialog(gpointer data)
{
    GtkWidget *dialog = GTK_WIDGET(data);
    gtk_widget_destroy(dialog);
    gtk_main_quit();
    return FALSE;
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

	int  battery_percentage 	= get_battery_percentage();
	char *battery_status 		= get_battery_status();
	char *ac_adapter_status 	= get_ac_adapter_status();

	char percentageStr[32];
    snprintf(percentageStr, sizeof(percentageStr), "Battery Percentage: %d%%", battery_percentage);
    

	GtkWidget *dialog;
    GtkWidget *contentArea;
    GtkWidget *batteryStatusLabel;
    GtkWidget *acAdapterStatusLabel;
    GtkWidget *batteryPercentageLabel;
    
    dialog = gtk_message_dialog_new(NULL,
									GTK_DIALOG_MODAL,
									GTK_MESSAGE_OTHER,
									GTK_BUTTONS_NONE,
									NULL);

	gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 200);								
	contentArea = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    batteryStatusLabel = gtk_label_new(battery_status);
    gtk_box_pack_start(GTK_BOX(contentArea), batteryStatusLabel, TRUE, TRUE, 0);
    
    batteryPercentageLabel = gtk_label_new(percentageStr);
    gtk_box_pack_start(GTK_BOX(contentArea), batteryPercentageLabel, TRUE, TRUE, 0);

	acAdapterStatusLabel = gtk_label_new(ac_adapter_status);
    gtk_box_pack_start(GTK_BOX(contentArea), acAdapterStatusLabel, TRUE, TRUE, 0);


    g_timeout_add_seconds(TIMER_FOR_CLOSES, close_dialog, dialog);

    gtk_widget_show_all(dialog);

    gtk_main();

    return 0;
}