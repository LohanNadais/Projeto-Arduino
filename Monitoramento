import serial
import time

# Configuração da porta serial
porta_serial = 'COM3'  
baud_rate = 9600     

try:
    # conectando porta serial
    arduino = serial.Serial(porta_serial, baud_rate)
    print("Conectado ao Arduino com sucesso.")
except serial.SerialException:
    print("Nao foi possivel conectar ao Arduino.")  
    exit()

time.sleep(2)  # para garantir que a conexão serial está estável

print("Monitorando o estado...")

try:
    while True:
        if arduino.in_waiting > 0:  # Verificando se ha dados disponiveis para leitura
            linha = arduino.readline().decode('utf-8').strip()
            if linha == "OCUPADO":
                print("Estado: OCUPADO")
            elif linha == "VAGO":
                print("Estado: VAGO")
        time.sleep(1)  # Verifica a cada segundo
except KeyboardInterrupt:
    print("\nMonitoramento interrompido pelo usuario.")  
finally:
    arduino.close()
    print("Conexao serial encerrada.")
