## Philosophers

Mutex Synchronisation :
https://youtu.be/GXXE42bkqQk

Mutex man :
https://linux.die.net/man/3/pthread_mutex_init

Semaphores with Threads:
https://mtodorovic.developpez.com/linux/programmation-avancee/?page=page_4#L4-4-5

TODO:

NORME

all: remplacer pthread_exit() par un simple return(), elle est pas autorisée !

philo_one : problème de logique : si il y a un seul pilosophe il meurt car il n'y a qu'une seule fourchette et il doit se servrir de 2 fourchettes pour manger

philo_three


si CTRL-C when semaphore
on execute pas les instructions finale
qui consistent entre autre a del le semaphore
a la prochaine exec, on réouvre le sémaphore précédent
qui vaut 0
donc ça wait-inf
lancer avec 0 philosophes pour débloquer
ça passera dans simulation_delete
qui unlink et close le semaphore
ensuite on peut relancer normalement

Stop the waiting :
https://stackoverflow.com/questions/47317048/how-to-exit-from-thread-which-is-suspended-by-semaphore
