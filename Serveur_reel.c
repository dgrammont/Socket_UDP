/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dgrammont
 *
 * Created on 8 septembre 2020, 10:50
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int soc; //la socket
    struct sockaddr_in infoClient;
    struct sockaddr_in infoServeur;
    float donneAEnvoyer;
    float donneRecue;
    int retour;
    int taille;
    

    // creation de la socket en mode datagram
    soc = socket(PF_INET, SOCK_DGRAM, 0/*IPROTO_UDP*/);
    if (soc == -1) {
        printf("pb creation socket : %s \n", strerror(errno));
        exit(errno);
    }
    //initialisation de la structure contenatn les infos du serveur
    infoServeur.sin_family = AF_INET;
    infoServeur.sin_port = htons(3333);
    infoServeur.sin_addr.s_addr = htonl(INADDR_ANY);
    //infoServeur.sin_zero =0;
    retour=bind(soc, &infoServeur, sizeof(infoServeur));
    //recevoir la donnee en provenance du serveur
    retour = recvfrom(
            soc, &donneRecue
            , sizeof (donneRecue)
            , 0
            , (struct sockaddr *) &infoClient
            , &taille);
    if (retour == -1) {

        printf("pb recvfrom : %s \n", strerror(errno));
        exit(errno);
    }
    donneAEnvoyer= donneRecue *-1;
   //
    printf("Donne recue  de %s/%d : %f \n", inet_ntoa(infoClient.sin_addr),infoClient.sin_port,donneRecue);
     //envoyer la donnee au serveur 
    retour=sendto(soc,&donneAEnvoyer
            ,sizeof(donneAEnvoyer)
            ,0
            ,(struct sockaddr *)&infoClient
            ,sizeof(infoClient));
    if (soc ==-1)
    {
        printf("pb sendto : %s \n",strerror(errno));
        exit(errno);
    }
     // afficher la donnee
   
    //fermer la socket
    close(soc);
    return (EXIT_SUCCESS);
}

