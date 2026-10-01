# On utilise une image Python légère (PlatformIO est basé sur Python)
FROM python:3.11-slim

# Installer les dépendances système minimales
RUN apt-get update && apt-get install -y git curl && rm -rf /var/lib/apt/lists/*

# Installer PlatformIO Core
RUN pip install -U platformio

# Définir le dossier de travail
WORKDIR /workspace

# Copier uniquement le fichier de configuration pour pré-installer les outils et bibliothèques
COPY platformio.ini .

RUN echo "[secrets]" > secrets.ini \
    && echo "build_flags =" >> secrets.ini \
    && echo "esp_ip = 127.0.0.1" >> secrets.ini

# Pré-installer les plateformes et bibliothèques pour gagner du temps au build
RUN pio pkg install

# Copier le reste du code (src, lib, etc.)
COPY . .

# Par défaut, quand on lance le conteneur, il compile le projet
CMD ["pio", "run"]
