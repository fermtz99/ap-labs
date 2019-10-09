
int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);

int main() {
	infof("Informacion simple\n");
	warnf("Un warning\n");
	//panicf("Modo de panico\n");
	errorf("Error en el codigo\n");
	panicf("Modo de panico\n");
	return 0;
}
