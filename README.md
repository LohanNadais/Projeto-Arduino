# 💡 Detecção de Ocupação de Leitos Hospitalares com Arduino

Este projeto utiliza um sensor de peso em um leito hospitalar, integrado a um Arduino, para detectar automaticamente se o leito está **ocupado** ou **vago**. O objetivo é otimizar o controle de ocupação sem que enfermeiros precisem sair da recepção para fazer essa checagem manualmente.

> ⚙️ Devido à falta de recursos físicos, o projeto foi desenvolvido e testado no **Tinkercad**, um simulador online de Arduino.

---

## 📌 Funcionalidades

- Detecta automaticamente se há alguém no leito com base na leitura de um sensor de peso.
- Registra o status ("OCUPADO" ou "VAGO") após 10 minutos de permanência no mesmo estado.
- Envia os dados via comunicação serial para um script em Python.
- O script Python registra os eventos em um arquivo `.txt` com data e hora.

---

## 🛠 Tecnologias Utilizadas

- **Arduino UNO** (simulado no Tinkercad)  
- **Sensor de força (peso)** simulado via entrada analógica  
- **IDE Arduino**  
- **Python 3** para leitura serial e registro de logs  

---

## 🚀 Como Funciona

### Arduino
- Lê a entrada analógica do sensor de peso.
- Se a força estiver acima de um limite (2.0 N), considera o leito como **ocupado**.
- Se abaixo, considera como **vago**.
- Após 10 minutos no mesmo estado, envia `"OCUPADO"` ou `"VAGO"` via serial.

### Python
- Lê a porta serial (ex: COM3) continuamente.
- Detecta mudanças no status do leito.
- Registra cada alteração no arquivo `log_status.txt` com data e hora.

---

## 🔧 Código Arduino (Resumo)

```cpp
const int sensorPin = A0;
const float limite = 2.0;
const unsigned long intervalo = 10 * 60 * 1000;

if (force >= limite) {
  if (!estadoOcupado) { estadoOcupado = true; tempoUltimoEstado = tempoAtual; }
  else if (tempoAtual - tempoUltimoEstado >= intervalo) Serial.println("OCUPADO");
} else {
  if (estadoOcupado) { estadoOcupado = false; tempoUltimoEstado = tempoAtual; }
  else if (tempoAtual - tempoUltimoEstado >= intervalo) Serial.println("VAGO");
}
```
---
## 🐍 Código Python (Resumo)

```cpp
def registrar_status(status):
    horario = datetime.now().strftime("%d/%m/%Y - %H:%M")
    with open("log_status.txt", "a") as f:
        f.write(f"{status} - {horario}\\n")

if linha in ["OCUPADO", "VAGO"] and linha != ultimo_status:
    registrar_status(linha)
    ultimo_status = linha
```

---


##📈 Resultados Esperados
- Redução de trabalho manual da equipe de enfermagem.
- Registro confiável de ocupação de leitos.
- Base para integração com sistemas maiores de gestão hospitalar.

---

##📎 Possíveis Melhorias Futuras
- Uso de placas com Wi-Fi (ex: ESP32) para comunicação com banco de dados online.
- Dashboard web para visualização em tempo real.
- Alerta visual ou sonoro no painel da recepção.

---

#👤 Autor

**Lohan Nadais da Silva**
