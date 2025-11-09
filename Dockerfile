# Choisir une image de base avec les outils pour compiler en C  
FROM debian:latest

# Installer les outils nécessaires  
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    libreadline-dev \
    && rm -rf /var/lib/apt/lists/*

# Créer un répertoire de travail  
WORKDIR /app

# Cloner le dépôt  
RUN git clone https://github.com/timothee-maker/mini_shell_42.git .

# Copier le Makefile / sources (optionnel si déjà présent)  
# COPY . /app

# Compiler le projet  
RUN make

# Définir le point d’entrée / commande par défaut  
CMD ["./minishell"]
