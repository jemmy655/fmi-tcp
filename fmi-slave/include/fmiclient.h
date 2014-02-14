/*
 * 
 * @author Adeel Asghar <adeel.asghar@liu.se>
 *
 * Created on: Nov 13, 2013
 *
 */

#ifndef FMICLIENT_H_
#define FMICLIENT_H_

#include "main.h"

typedef struct {
  int logLevel;
  jm_callbacks JMCallbacks;
  fmi_import_context_t* importContext;
  fmi1_fmu_kind_enu_t fmuType;
  fmi1_callback_functions_t FMI1CallbackFunctions;
  fmi2_callback_functions_t FMI2CallbackFunctions;
  char* workingDirectory;
  fmi_version_enu_t version;
  fmi1_import_t* FMI1ImportInstance;
  fmi2_import_t* FMI2ImportInstance;
  char* instanceName;
  int debugLogging;
  char* fmuLocation;
  char* mimeType;
  double timeOut;
  int visible;
  int interactive;
  double tStart;
  double currentTime;
  double stepSize;
  int stopTimeDefined;
  double tStop;
  fmi1_import_variable_list_t* FMI1Variables;
  fmi2_import_variable_list_t* FMI2Variables;
  /*
   * TCP Client fields
   */
  lw_pump pump;
  lw_client client;
} FMICoSimulationClient;

FMICoSimulationClient* createFMICoSimulationClient(const char* fileName, int loggingOn, int debugLogging);
void destroyFMICoSimulationClient(FMICoSimulationClient *FMICSClient);

void sendCommand(lw_client client, char* data, size_t size);

/* FMI 1.0 wrapper functions */
jm_status_enu_t fmi1InstantiateSlaveWrapper(FMICoSimulationClient *FMICSClient);
fmi1_status_t fmi1InitializeSlaveWrapper(FMICoSimulationClient *FMICSClient);
void fmi1SetInitialValues(FMICoSimulationClient *FMICSClient);
fmi1_import_variable_t* fmi1GetVariableByVr(FMICoSimulationClient *FMICSClient, int valueReference);
void fmi1GetValue(FMICoSimulationClient *FMICSClient, int valueReference, char* retVal);
void fmi1SetValue(FMICoSimulationClient *FMICSClient, int valueReference, const char* data, const char* name);
fmi1_status_t fmi1DoStep(FMICoSimulationClient *FMICSClient, int *finished);
fmi1_status_t fmi1PendingStatusString(FMICoSimulationClient *FMICSClient, fmi1_string_t *str);
fmi1_status_t fmi1DoStepStatus(FMICoSimulationClient *FMICSClient, fmi1_status_t *status);

/* FMI 2.0 wrapper functions */
jm_status_enu_t fmi2InstantiateSlaveWrapper(FMICoSimulationClient *FMICSClient);

void connectClient(FMICoSimulationClient *FMICSClient, const char* hostName, int port);
void clientOnConnect(lw_client client);
void clientOnData(lw_client client, const char* data, long size);
void fmi1ClientOnData(FMICoSimulationClient *FMICSClient, lw_client client, const char* token);
void fmi2ClientOnData(FMICoSimulationClient *FMICSClient, lw_client client, const char* token);
void clientOnDisconnect(lw_client client);
void clientOnError(lw_client client, lw_error error);

#endif /* FMICLIENT_H_ */
