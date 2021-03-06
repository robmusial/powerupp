#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "variables.h"
#include "defaults.h"
 
// TODO: sort
int set_limits_from_pp_table() {
  gint ival;
  float fpower = 0;
  float fpowerlimitupper;
  float fpowerlimitlower;
  char vallines[20][200];
  char limlines[20][200];
  size_t linenum = 0;
  FILE *fgetvalues = NULL;
  FILE *fgetlimits = NULL;

  if (gl_revtable == 12) {
    fgetvalues = popen(getvalues_navi10, "r");
    fgetlimits = popen(getlimits_navi10, "r");
  }

  // read values and set them as limits since no limits exist
  if (fgetvalues != NULL) {
    printf("Getting values to use as limits from pp_table:\n");
    while (linenum < 20 && fgets(vallines[linenum], sizeof(*vallines), fgetvalues) != NULL) {
      ++linenum;
    }
    for (size_t i = 0; i < linenum; i++) {
      size_t len = strlen(vallines[i]);
      if (len > 0 && vallines[i][len-1] == '\n') {
        vallines[i][--len] = '\0';
      }
      puts(vallines[i]);
      }
    pclose(fgetvalues);
  }

  // read limits where they exist
  linenum = 0;
  if (fgetlimits != NULL) {
    printf("Getting limits from pp_table:\n");
    while (linenum < 20 && fgets(limlines[linenum], sizeof(*limlines), fgetlimits) != NULL) {
      ++linenum;
    }
    for (size_t i = 0; i < linenum; i++) {
      size_t len = strlen(limlines[i]);
      if (len > 0 && limlines[i][len-1] == '\n') {
        limlines[i][--len] = '\0';
      }
      puts(limlines[i]);
      }
    pclose(fgetlimits);
  }  

  ival = atoi(vallines[17]);
  if (ival != 0) {
    ival = ival / 4;
    socvoltlimitlower = ival;
    socvoltlimitupper = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_socvolt), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_socvolt), ival);
  }

  ival = atoi(vallines[16]);
  if (ival != 0) {
    ival = ival / 4;
    socvoltminlimitlower = ival;
    socvoltminlimitupper = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_socvoltmin), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_socvoltmin), ival);
  }
  
  ival = atoi(vallines[0]);
  if (ival != 0) {
    ival = ival / 4;
    gfxvoltminlimitlower = ival;
    gfxvoltminlimitupper = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_gfxvoltmin), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_gfxvoltmin), ival);
  }

  ival = atoi(vallines[18]);
  if (ival != 0) {
    socclocklimitlower = ival;
    socclocklimitupper = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_socclock), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_socclock), ival);
  }

  ival = atoi(vallines[19]);
  if (ival != 0) {
    voltoffsetlimitlower = ival;
    voltoffsetlimitupper = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_voltoffset), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_voltoffset), ival);
  }

  // DPM 0
  ival = atoi(vallines[4]);
  if (ival != 0) {
    ival = ival / 4;
    memmvddvoltlimitlower0 = ival;
    memmvddvoltlimitupper0 = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_memmvddvolt0), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_memmvddvolt0), ival);
  }

  ival = atoi(vallines[8]);
  if (ival != 0) {
    ival = ival / 4;
    memvddcivoltlimitlower0 = ival;
    memvddcivoltlimitupper0 = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_memvddcivolt0), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_memvddcivolt0), ival);
  }

  ival = atoi(vallines[12]);
  if (ival != 0) {
    memclocklimitlower0 = ival;
    memclocklimitupper0 = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_memclock0), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_memclock0), ival);
  }

  // DPM 1
  ival = atoi(vallines[5]);
  if (ival != 0) {
    ival = ival / 4;
    memmvddvoltlimitlower1 = ival;
    memmvddvoltlimitupper1 = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_memmvddvolt1), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_memmvddvolt1), ival);
  }

  ival = atoi(vallines[9]);
  if (ival != 0) {
    ival = ival / 4;
    memvddcivoltlimitlower1 = ival;
    memvddcivoltlimitupper1 = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_memvddcivolt1), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_memvddcivolt1), ival);
  }

  ival = atoi(vallines[13]);
  if (ival != 0) {
    memclocklimitlower1 = ival;
    memclocklimitupper1 = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_memclock1), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_memclock1), ival);
  }

  // DPM 2
  ival = atoi(vallines[6]);
  if (ival != 0) {
    ival = ival / 4;
    memmvddvoltlimitlower2 = ival;
    memmvddvoltlimitupper2 = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_memmvddvolt2), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_memmvddvolt2), ival);
  }

  ival = atoi(vallines[10]);
  if (ival != 0) {
    ival = ival / 4;
    memvddcivoltlimitlower2 = ival;
    memvddcivoltlimitupper2 = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_memvddcivolt2), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_memvddcivolt2), ival);
  }

  ival = atoi(vallines[14]);
  if (ival != 0) {
    memclocklimitlower2 = ival;
    memclocklimitupper2 = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_memclock2), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_memclock2), ival);
  }

  // DPM 3
  ival = atoi(vallines[7]);
  if (ival != 0) {
    ival = ival / 4;
    memmvddvoltlimitlower = ival;
    memmvddvoltlimitupper = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_memmvddvolt), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_memmvddvolt), ival);
  }

  ival = atoi(vallines[11]);
  if (ival != 0) {
    ival = ival / 4;
    memvddcivoltlimitlower = ival;
    memvddcivoltlimitupper = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_memvddcivolt), ival);
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_memvddcivolt), ival);
  }

  ival = atoi(vallines[3]);
  if (ival != 0) {
    fpower = ival;
  }
  // below are actual pp table limits, power depends on value as it is percentage limited
  if (fpower != 0) {
    fpowerlimitlower = (float)atoi(limlines[6]);
    if (fpowerlimitlower != 0) {
      ival = fpower - (fpower * (1- fpowerlimitlower / (float)100));
      gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_gpupower), ival);
      gpupowerlimitlower = ival;
    }
  }
  if (fpower != 0) {
    fpowerlimitupper = (float)atoi(limlines[2]);
    if (fpowerlimitupper != 0) {
      ival = fpower + (fpower * fpowerlimitupper / (float)100);
      gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_gpupower), ival);
      gpupowerlimitupper = ival;
    }
  }

  ival = atoi(limlines[5]);
  if (ival != 0) {
    gfxvoltlimitlower = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_gfxvolt), ival);
  }
  
  ival = atoi(limlines[1]);
  if (ival != 0) {
    gfxvoltlimitupper = ival;
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_gfxvolt), ival);
  }

  ival = atoi(limlines[4]);
  if (ival != 0) {
    gfxclocklimitlower = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_gfxclock), ival);
  }
  
  ival = atoi(limlines[0]);
  if (ival != 0) {
    gfxclocklimitupper = ival;
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_gfxclock), ival);
  }

  ival = atoi(limlines[7]);
  if (ival != 0) {
    memclocklimitlower = ival;
    gtk_adjustment_set_lower(GTK_ADJUSTMENT(g_adj_memclock), ival);
  }
  
  ival = atoi(limlines[3]);
  if (ival != 0) {
    memclocklimitupper = ival;
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(g_adj_memclock), ival);
  }
  return 0;
}

int set_values_from_pp_table(app_widgets *app_wdgts) {
  gint ival;
  char vallines[20][200];
  size_t linenum = 0;
  FILE *fgetvalues = NULL;

  if (gl_revtable == 12) {
    fgetvalues = popen(getvalues_navi10, "r");
  }

  if (fgetvalues != NULL) {
    printf("Getting values from pp_table:\n");
    while (linenum < 20 && fgets(vallines[linenum], sizeof(*vallines), fgetvalues) != NULL) {
      ++linenum;
    }
    for (size_t i = 0; i < linenum; i++) {
      size_t len = strlen(vallines[i]);
      if (len > 0 && vallines[i][len-1] == '\n') {
        vallines[i][--len] = '\0';
      }
      puts(vallines[i]);
      }
    pclose(fgetvalues);
  }

  ival = atoi(vallines[0]);
  if (ival != 0) {
    ival = ival / 4;
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_gfxvoltmin),TRUE); 
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_gfxvoltmin),TRUE); 
    if (gfxvoltminlimitlower > ival || ival > gfxvoltminlimitupper) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_gfxvoltmin), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_gfxvoltmin), "N/A");
  }

  ival = atoi(vallines[1]);
  if (ival != 0) {
    ival = ival / 4;
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_gfxvolt),TRUE); 
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_gfxvolt),TRUE); 
    if (gfxvoltlimitlower > ival || ival > gfxvoltlimitupper) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_gfxvolt), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_gfxvolt), "N/A");
  }

  ival = atoi(vallines[2]);
  if (ival != 0) {
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_gfxclock),TRUE); 
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_gfxclock),TRUE); 
    if (gfxclocklimitlower > ival || ival > gfxclocklimitupper) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_gfxclock), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_gfxclock), "N/A");
  }

  ival = atoi(vallines[3]);
  if (ival != 0) {
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_gpupower),TRUE); 
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_gpupower),TRUE); 
    if (gpupowerlimitlower > ival || ival > gpupowerlimitupper) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_gpupower), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_gpupower), "N/A");
  }

  ival = atoi(vallines[16]);
  if (ival != 0) {
    ival = ival / 4;
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_socvoltmin),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_socvoltmin),TRUE); 
    if (socvoltminlimitlower > ival || ival > socvoltminlimitupper) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_socvoltmin), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_socvoltmin), "N/A");
  }

  ival = atoi(vallines[17]);
  if (ival != 0) {
    ival = ival / 4;
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_socvolt),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_socvolt),TRUE); 
    if (socvoltlimitlower > ival || ival > socvoltlimitupper) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_socvolt), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_socvolt), "N/A");
  }

  ival = atoi(vallines[18]);
  if (ival != 0) {
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_socclock),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_socclock),TRUE); 
    if (socclocklimitlower > ival || ival > socclocklimitupper) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_socclock), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_socclock), "N/A");
  }

  float fval;
  fval = atof(vallines[19]) * 1000;
  ival = fval;
  gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_voltoffset),TRUE);
  gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_voltoffset),TRUE); 
  if (voltoffsetlimitlower > ival || ival > voltoffsetlimitupper) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
  }
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_voltoffset), ival);
 

  // DPM 0
  ival = atoi(vallines[4]);
  if (ival != 0) {
    ival = ival / 4;
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_memmvddvolt0),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_memmvddvolt0),TRUE); 
    if (memmvddvoltlimitlower0 > ival || ival > memmvddvoltlimitupper0) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_memmvddvolt0), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_memmvddvolt0), "N/A");
  }

  ival = atoi(vallines[8]);
  if (ival != 0) {
    ival = ival / 4;
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_memvddcivolt0),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_memvddcivolt0),TRUE); 
    if (memvddcivoltlimitlower0 > ival || ival > memvddcivoltlimitupper0) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_memvddcivolt0), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_memvddcivolt0), "N/A");
  }

  ival = atoi(vallines[12]);
  if (ival != 0) {
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_memclock0),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_memclock0),TRUE); 
    if (memclocklimitlower0 > ival || ival > memclocklimitupper0) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_memclock0), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_memclock0), "N/A");
  }

  // DPM 1
  ival = atoi(vallines[5]);
  if (ival != 0) {
    ival = ival / 4;
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_memmvddvolt1),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_memmvddvolt1),TRUE); 
    if (memmvddvoltlimitlower1 > ival || ival > memmvddvoltlimitupper1) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_memmvddvolt1), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_memmvddvolt1), "N/A");
  }

  ival = atoi(vallines[9]);
  if (ival != 0) {
    ival = ival / 4;
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_memvddcivolt1),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_memvddcivolt1),TRUE); 
    if (memvddcivoltlimitlower1 > ival || ival > memvddcivoltlimitupper1) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_memvddcivolt1), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_memvddcivolt1), "N/A");
  }

  ival = atoi(vallines[13]);
  if (ival != 0) {
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_memclock1),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_memclock1),TRUE); 
    if (memclocklimitlower1 > ival || ival > memclocklimitupper1) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_memclock1), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_memclock1), "N/A");
  }

  // DPM 2
  ival = atoi(vallines[6]);
  if (ival != 0) {
    ival = ival / 4;
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_memmvddvolt2),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_memmvddvolt2),TRUE); 
    if (memmvddvoltlimitlower2 > ival || ival > memmvddvoltlimitupper2) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_memmvddvolt2), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_memmvddvolt2), "N/A");
  }

  ival = atoi(vallines[10]);
  if (ival != 0) {
    ival = ival / 4;
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_memvddcivolt2),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_memvddcivolt2),TRUE); 
    if (memvddcivoltlimitlower2 > ival || ival > memvddcivoltlimitupper2) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_memvddcivolt2), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_memvddcivolt2), "N/A");
  }

  ival = atoi(vallines[14]);
  if (ival != 0) {
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_memclock2),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_memclock2),TRUE); 
    if (memclocklimitlower2 > ival || ival > memclocklimitupper2) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_memclock2), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_memclock2), "N/A");
  }

  // DPM 3
  ival = atoi(vallines[7]);
  if (ival != 0) {
    ival = ival / 4;
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_memmvddvolt),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_memmvddvolt),TRUE); 
    if (memmvddvoltlimitlower > ival || ival > memmvddvoltlimitupper) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_memmvddvolt), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_memmvddvolt), "N/A");
  }

  ival = atoi(vallines[11]);
  if (ival != 0) {
    ival = ival / 4;
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_memvddcivolt),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_memvddcivolt),TRUE); 
    if (memvddcivoltlimitlower > ival || ival > memvddcivoltlimitupper) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_memvddcivolt), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_memvddcivolt), "N/A");
  }

  ival = atoi(vallines[15]);
  if (ival != 0) {
    gtk_editable_set_editable(GTK_EDITABLE(app_wdgts->g_edit_memclock),TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_edit_memclock),TRUE); 
    if (memclocklimitlower > ival || ival > memclocklimitupper) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), TRUE);
    }
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_memclock), ival);
  }
  else {
    gtk_entry_set_text (GTK_ENTRY (app_wdgts->g_edit_memclock), "N/A");
  }

  return 0;
}

const char *values_to_keyfile(app_widgets *app_wdgts) {
  g_autoptr(GKeyFile) temp_key_file = g_key_file_new ();
  gsize keysize;
  // Fill data to values
  int igfxvolt = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_gfxvolt));
  int igfxvoltmin = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_gfxvoltmin));
  int igpupower = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_gpupower));
  int igfxclock = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_gfxclock));
  int imemmvddvolt = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_memmvddvolt));
  int imemvddcivolt = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_memvddcivolt));
  int imemclock = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_memclock));
  int isocvolt = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_socvolt));
  int isocvoltmin = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_socvoltmin));
  int isocclock = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_socclock));
  int ivoltoffset = gtk_spin_button_get_value(GTK_SPIN_BUTTON(app_wdgts->g_edit_voltoffset));
  int imemmvddvolt0 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_memmvddvolt0));
  int imemvddcivolt0 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_memvddcivolt0));
  int imemclock0 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_memclock0));
  int imemmvddvolt1 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_memmvddvolt1));
  int imemvddcivolt1 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_memvddcivolt1));
  int imemclock1 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_memclock1));
  int imemmvddvolt2 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_memmvddvolt2));
  int imemvddcivolt2 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_memvddcivolt2));
  int imemclock2 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->g_edit_memclock2));

  // TODO: add more GPU families
  if (gl_revtable == 12) {
    g_key_file_set_integer (temp_key_file, "Values", "gfxvolt", igfxvolt);
    g_key_file_set_integer (temp_key_file, "Values", "gfxvoltmin", igfxvoltmin);
    g_key_file_set_integer (temp_key_file, "Values", "gpupower", igpupower);
    g_key_file_set_integer (temp_key_file, "Values", "gfxclock", igfxclock);
    g_key_file_set_integer (temp_key_file, "Values", "memmvddvolt", imemmvddvolt);
    g_key_file_set_integer (temp_key_file, "Values", "memvddcivolt", imemvddcivolt);
    g_key_file_set_integer (temp_key_file, "Values", "memclock", imemclock);
    g_key_file_set_integer (temp_key_file, "Values", "socvolt", isocvolt);
    g_key_file_set_integer (temp_key_file, "Values", "socvoltmin", isocvoltmin);
    g_key_file_set_integer (temp_key_file, "Values", "socclock", isocclock);
    g_key_file_set_integer (temp_key_file, "Values", "voltoffset", ivoltoffset);
    g_key_file_set_integer (temp_key_file, "Values", "memmvddvolt0", imemmvddvolt0);
    g_key_file_set_integer (temp_key_file, "Values", "memvddcivolt0", imemvddcivolt0);
    g_key_file_set_integer (temp_key_file, "Values", "memclock0", imemclock0);
    g_key_file_set_integer (temp_key_file, "Values", "memmvddvolt1", imemmvddvolt1);
    g_key_file_set_integer (temp_key_file, "Values", "memvddcivolt1", imemvddcivolt1);
    g_key_file_set_integer (temp_key_file, "Values", "memclock1", imemclock1);
    g_key_file_set_integer (temp_key_file, "Values", "memmvddvolt2", imemmvddvolt2);
    g_key_file_set_integer (temp_key_file, "Values", "memvddcivolt2", imemvddcivolt2);
    g_key_file_set_integer (temp_key_file, "Values", "memclock2", imemclock2);

    g_key_file_set_integer (temp_key_file, "Limits", "gfxvoltlimitlower", gfxvoltlimitlower);
    g_key_file_set_integer (temp_key_file, "Limits", "gfxvoltlimitupper", gfxvoltlimitupper);
    g_key_file_set_integer (temp_key_file, "Limits", "gfxclocklimitlower", gfxclocklimitlower);
    g_key_file_set_integer (temp_key_file, "Limits", "gfxclocklimitupper", gfxclocklimitupper);
    g_key_file_set_integer (temp_key_file, "Limits", "gpupowerlimitlower", gpupowerlimitlower);
    g_key_file_set_integer (temp_key_file, "Limits", "gpupowerlimitupper", gpupowerlimitupper);
    g_key_file_set_integer (temp_key_file, "Limits", "memmvddvoltlimitlower", memmvddvoltlimitlower);
    g_key_file_set_integer (temp_key_file, "Limits", "memmvddvoltlimitupper", memmvddvoltlimitupper);
    g_key_file_set_integer (temp_key_file, "Limits", "memvddcivoltlimitlower", memvddcivoltlimitlower);
    g_key_file_set_integer (temp_key_file, "Limits", "memvddcivoltlimitupper", memvddcivoltlimitupper);
    g_key_file_set_integer (temp_key_file, "Limits", "memclocklimitlower", memclocklimitlower);
    g_key_file_set_integer (temp_key_file, "Limits", "memclocklimitupper", memclocklimitupper);
    g_key_file_set_integer (temp_key_file, "Limits", "socvoltlimitlower", socvoltlimitlower);
    g_key_file_set_integer (temp_key_file, "Limits", "socvoltlimitupper", socvoltlimitupper);
    g_key_file_set_integer (temp_key_file, "Limits", "socclocklimitlower", socclocklimitlower);
    g_key_file_set_integer (temp_key_file, "Limits", "socclocklimitupper", socclocklimitupper);
    g_key_file_set_integer (temp_key_file, "Limits", "voltoffsetlimitlower", voltoffsetlimitlower);
    g_key_file_set_integer (temp_key_file, "Limits", "voltoffsetlimitupper", voltoffsetlimitupper);
    g_key_file_set_integer (temp_key_file, "Limits", "memmvddvoltlimitlower0", memmvddvoltlimitlower0);
    g_key_file_set_integer (temp_key_file, "Limits", "memmvddvoltlimitupper0", memmvddvoltlimitupper0);
    g_key_file_set_integer (temp_key_file, "Limits", "memvddcivoltlimitlower0", memvddcivoltlimitlower0);
    g_key_file_set_integer (temp_key_file, "Limits", "memvddcivoltlimitupper0", memvddcivoltlimitupper0);
    g_key_file_set_integer (temp_key_file, "Limits", "memclocklimitlower0", memclocklimitlower0);
    g_key_file_set_integer (temp_key_file, "Limits", "memclocklimitupper0", memclocklimitupper0);
    g_key_file_set_integer (temp_key_file, "Limits", "memmvddvoltlimitlower1", memmvddvoltlimitlower1);
    g_key_file_set_integer (temp_key_file, "Limits", "memmvddvoltlimitupper1", memmvddvoltlimitupper1);
    g_key_file_set_integer (temp_key_file, "Limits", "memvddcivoltlimitlower1", memvddcivoltlimitlower1);
    g_key_file_set_integer (temp_key_file, "Limits", "memvddcivoltlimitupper1", memvddcivoltlimitupper1);
    g_key_file_set_integer (temp_key_file, "Limits", "memclocklimitlower1", memclocklimitlower1);
    g_key_file_set_integer (temp_key_file, "Limits", "memclocklimitupper1", memclocklimitupper1);
    g_key_file_set_integer (temp_key_file, "Limits", "memmvddvoltlimitlower2", memmvddvoltlimitlower2);
    g_key_file_set_integer (temp_key_file, "Limits", "memmvddvoltlimitupper2", memmvddvoltlimitupper2);
    g_key_file_set_integer (temp_key_file, "Limits", "memvddcivoltlimitlower2", memvddcivoltlimitlower2);
    g_key_file_set_integer (temp_key_file, "Limits", "memvddcivoltlimitupper2", memvddcivoltlimitupper2);
    g_key_file_set_integer (temp_key_file, "Limits", "memclocklimitlower2", memclocklimitlower2);
    g_key_file_set_integer (temp_key_file, "Limits", "memclocklimitupper2", memclocklimitupper2);
    g_key_file_set_integer (temp_key_file, "Limits", "gfxvoltminlimitlower", gfxvoltminlimitlower);
    g_key_file_set_integer (temp_key_file, "Limits", "gfxvoltminlimitupper", gfxvoltminlimitupper);
    g_key_file_set_integer (temp_key_file, "Limits", "socvoltminlimitlower", socvoltminlimitlower);
    g_key_file_set_integer (temp_key_file, "Limits", "socvoltminlimitupper", socvoltminlimitupper);    
  }
  const char *key_data = g_key_file_to_data (temp_key_file, &keysize, NULL);
  g_key_file_free (temp_key_file);
  return key_data;
}

int save_defaults_settings(app_widgets *app_wdgts) {
  int goodtowrite = 0;
  int writeerror = 0;
  gsize limitslength;
  gsize valueslength;
  gsize deflimitslength;
  gsize defvalueslength;

  g_autoptr(GKeyFile) defkey_file = g_key_file_new ();
  g_autoptr(GError) error = NULL;
  g_autoptr(GKeyFile) key_file = g_key_file_new();

  const char *key_data = values_to_keyfile(app_wdgts);

  if (!g_key_file_load_from_data(key_file, key_data, -1, G_KEY_FILE_NONE, NULL)) {
    printf("Error reading current values\n");
    return 1;
  }
  else {
    // get number of settings to write
    g_key_file_get_keys (key_file, "Values", &valueslength, NULL);
    g_key_file_get_keys (key_file, "Limits", &limitslength, NULL);
  }


  // load defaults file
  if(access(defsettingspath, F_OK) != -1) { 
    if (!g_key_file_load_from_file(defkey_file, defsettingspath, G_KEY_FILE_NONE, &error)) {
      if (g_error_matches(error, G_FILE_ERROR, G_FILE_ERROR_NOENT)) {
        printf("Error loading settings file\n");
        // settings file loading error, write it
        goodtowrite = 1;
      }
    }
    else {
      // default settings file exist, count the number of settings in it
      g_key_file_get_keys (defkey_file, "Values", &defvalueslength, NULL);
      g_key_file_get_keys (defkey_file, "Limits", &deflimitslength, NULL);
      //overwrite if there are different number of settings to write than exisiting
      if ((defvalueslength + deflimitslength) != (valueslength + limitslength)) {
        printf("Default file has %ld settings and there are %ld settings to write, overwriting default settings file\n", defvalueslength + deflimitslength, valueslength + limitslength);
        goodtowrite = 1;
      }
      else {
        // default settings file has same number of settings, don't overwrite
        printf("Default file has %ld settings and there are %ld settings to write, not saving\n", defvalueslength + deflimitslength, valueslength + limitslength);
        goodtowrite = 0;
      }
    }
  }
  else {
    printf("No default file found, saving new defaults\n");
    goodtowrite = 1;
  }

  if (goodtowrite == 1) {
    // save to file
    printf("Saving current values as defaults settings in %s\n", defsettingspath);
    if (!g_key_file_save_to_file (key_file, defsettingspath, &error)) {
      printf("Unable to save defaults settings\n");
      gtk_text_buffer_set_text(GTK_TEXT_BUFFER(g_text_revealer), "Unable to save default settings", -1);
      gtk_revealer_set_reveal_child (GTK_REVEALER(app_wdgts->g_revealer), TRUE);
      writeerror = 1;
    }
    else {
      printf("Default data saved successfully\n");
      // if ok, enable load defaults button
      gtk_text_buffer_set_text(GTK_TEXT_BUFFER(g_text_revealer), "Active values loaded and saved as defaults", -1);
      gtk_revealer_set_reveal_child (GTK_REVEALER(app_wdgts->g_revealer), TRUE);
      gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_opt_defaults_load), TRUE);
    }
  }
  g_key_file_free (key_file);
  g_key_file_free (defkey_file);
  
  if (writeerror == 0) {
    return 0;
  }
  else {
    return 1;
  }
}

void on_btn_active_clicked(GtkButton *button, app_widgets *app_wdgts) {
  int readerror = 0;
  
  // untoggle to set it as it should be at the end
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app_wdgts->g_toggle_limits), FALSE);

  if (set_limits_from_file(defsettingspath) == 1) {
    // default settings exist but are outdated or corrupt, get data from pp table
    printf("No valid default settings, using data from pp_table\n");
    if (set_limits_from_pp_table(app_wdgts) != 0) {
      printf("Error getting default limits from pp table\n");
      readerror = 1;
      gtk_text_buffer_set_text(GTK_TEXT_BUFFER(g_text_revealer), "Error getting limits from pp table", -1);
      gtk_revealer_set_reveal_child (GTK_REVEALER(app_wdgts->g_revealer), TRUE);
    }
  }
  else {
    printf("Default settings loaded from defaults file\n");
  }

  if (readerror == 0) {
    if (set_values_from_pp_table(app_wdgts) != 0) {
      printf("Error getting values from pp table\n");
      readerror = 1;
    }
    else {
      printf("Values successfully loaded from pp table\n");
      gtk_text_buffer_set_text(GTK_TEXT_BUFFER(g_text_revealer), "Active values loaded", -1);
      gtk_revealer_set_reveal_child (GTK_REVEALER(app_wdgts->g_revealer), TRUE);
    }
  }

  // if getting data was ok, save it as default unless a default settings file already exists
  
  if (readerror == 0) {
    
    if (save_defaults_settings(app_wdgts) == 1) {
      printf("Error saving default settings\n");
      readerror = 1;
    }

    if (readerror == 0) {  
      // if all ok set apply and save buttons enabled
      gtk_widget_set_sensitive(GTK_WIDGET(g_btn_apply), TRUE);
      gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_opt_persistent_save), TRUE);
      gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_opt_profile_save), TRUE);
    }
    else {
      gtk_text_buffer_set_text(GTK_TEXT_BUFFER(g_text_revealer), "Error loading data, default settings not saved", -1);
      gtk_revealer_set_reveal_child (GTK_REVEALER(app_wdgts->g_revealer), TRUE);
      gtk_widget_set_sensitive(GTK_WIDGET(g_btn_apply), FALSE);
      gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_opt_persistent_save), FALSE);
      gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->g_opt_profile_save), FALSE);
    }  
  }
}