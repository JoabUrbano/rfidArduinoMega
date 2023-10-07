# rfidArduinoMega
Código dedicado a uma prática com RFID simulando uma tranca domestica. Quando inserirmos o cartão incorreto o LED alerta, e se o cartão errado é inserido variás vezes ele aciona um Buzzer de alerta e pisca o LED vermelho. Quando o cartão inserido é o correto, ele ascende o LED verde simulando a abertura da porta e zera as tentativas erradas anteriores.

Componentes utilizados:
- Arduino Mega
- Uma protoboard
- Um modulo MFRC522
- Duas tegs RFID
- Três resistores de 220 Ohm
- Um LED vermelho
- Um LED verde
- Um LED amarelo (Que substituiu o buzzer no projeto)
- Jumpers para as conexões

Bibliotecas necessarias:
- MFRC522