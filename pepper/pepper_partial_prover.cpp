//prover takes proving key, pws, computation inputs as input.
//generates outputs, proofs.


#include <libsnark/relations/constraint_satisfaction_problems/r1cs/r1cs.hpp>
#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>

#include <iostream>
#include <fstream>

#include <gmp.h>
#include "libv/computation_p.h"

#include "common_defs.h"

#ifndef NAME
#error "Must define NAME as name of computation."
#endif

int main (int argc, char* argv[]) {

    if (argc != 5) {
        std::cerr << "Fix your args!\n";
        std::cerr << "Need \"prover name.params name.pws name.inputs name.partial\"\n";
        exit(1);
    }

    struct comp_params p = parse_params(string(argv[1]));

    mpz_t prime;
    mpz_init_set_str(prime, "21888242871839275222246405745257275088548364400416034343698204186575808495617", 10);

    std::string input_fn = string(argv[3]);

    std::string partial_input_fn = string(argv[4]);
    std::ifstream partial_input_file;
    partial_input_file.open(partial_input_fn);

    int k;
    std::vector<int> F1_init;
    F1_init.reserve(p.n_vars);
    while (partial_input_file >> k) {
        F1_init.push_back(k);
    }

    if (F1_init.size() != p.n_vars) {
        std::cerr << "Bad var count in partial inputs..\n";
        exit(1);
    }

    ComputationProver prover(p.n_vars, p.n_constraints, p.n_inputs, p.n_outputs, prime, "default_shared_db", input_fn, false, F1_init);

    prover.compute_from_pws(argv[2]);
    prover.print_io();
}
