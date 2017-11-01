jPortable\bin\jar.exe xf ch*.jar WizardApp.class
jPortable\bin\javap.exe -c -private WizardApp.class > DeComp.txt
DEL /F WizardApp.class
