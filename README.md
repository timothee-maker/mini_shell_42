MINISHEll 42 | Par Timothée NOLENT et Louis DE GUILLEBON

Ce projet consite à reproduire un shell, en locurence, bash --posix dans notre cas.

Si vous êtes sur linux, vous avez juste a lancer make et l'executable se lancera.

Sinon, installer docker si ce n'est pas encore le cas.
Et lancer "docker build -t minishell ." ensuite "docker run -it --rm minishell".

Parsing : 
- Sépare chaque pipe de la ligne en une liste chainee de plusieurs elements par pipe
- Associe un token et un argument a chaque élément en fonction de leur nature (CMD, ARG, INFILE ...)
- Renvoie cette liste

Exec :
- Crée une structure pour chaque ligne
- Crée une commande par pipe
- Redirige tous les arguments et infile dans un fichier créé appelé ".infile"
- Redirige ".infile" sur STDIN au moment de l'execve
- Redirige un fichier nommé ".outfile" sur STDOUT au moment de l'execve
- Exécute la commande
- Affiche le contenu de ".outfile" si pas de pipe derriere
- Clear ".infile"
- Ajoute le contenu de ".outfile" dans ".infile" si il y a un pipe apres
- Clear ".outfile"
