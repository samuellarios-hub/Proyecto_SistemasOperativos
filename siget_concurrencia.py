import threading
import time
import random
from queue import Queue

MAX_BUFFER = 5  
buffer_trafico = Queue(maxsize=MAX_BUFFER)

def sensor_trafico(id_sensor):
    """Hilo Productor: Simula un sensor en una intersección."""
    while True:

        vehiculo_id = random.randint(1000, 9999)
        
        print(f" [Sensor {id_sensor}] Detectó vehículo: {vehiculo_id}")

        buffer_trafico.put(vehiculo_id)
        
        print(f" [Sensor {id_sensor}] Datos enviados al SIGET.")
        
        time.sleep(random.uniform(1, 3))

def modulo_analisis():
    """Hilo Consumidor: Procesa los datos para tomar decisiones de tráfico."""
    while True:
        
        datos = buffer_trafico.get()
        
        print(f" [Analizador] Procesando vehículo {datos}... Ajustando semáforos.")
        
        time.sleep(2)
        
        buffer_trafico.task_done()


        print(f"  [Analizador] Vehículo {datos} procesado con éxito.")

if __name__ == "__main__":
    print("... Iniciando Sistema de Tráfico Inteligente (SIGET) ...") 

    s1 = threading.Thread(target=sensor_trafico, args=(1,), daemon=True)
    s2 = threading.Thread(target=sensor_trafico, args=(2,), daemon=True)

    analizador = threading.Thread(target=modulo_analisis, daemon=True)

    s1.start()
    s2.start()
    analizador.start()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\n... Apagando sistema de tráfico ...")

        