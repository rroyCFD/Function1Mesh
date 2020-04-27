/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::Function1MeshTypes::damp

Description
    Ramp function base class for the set of scalar functions starting from 0 and
    increasing monotonically to 1 from \c start over the \c duration and
    remaining at 1 thereafter.

    Usage:
    \verbatim
        <entryName> <dampFunction>;
        <entryName>Coeffs
        {
            start     10;
            duration  20;
        }
    \endverbatim
    or
    \verbatim
        <entryName>
        {
            type      <dampFunction>;
            start     10;
            duration  20;
        }
    \endverbatim

    Where:
    \table
        Property | Description  | Required | Default value
        start    | Start time   | no       | 0
        duration | Duration     | yes      |
    \endtable

See also
    Foam::Function1Mesh

SourceFiles
    damp.C

\*---------------------------------------------------------------------------*/

#ifndef damp_H
#define damp_H

#include "Function1Mesh.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace Function1MeshTypes
{

/*---------------------------------------------------------------------------*\
                           Class damp Declaration
\*---------------------------------------------------------------------------*/

class damp
:
    public Function1Mesh<scalar>
{
protected:

    // Protected data

        //- Start-time of the damp function
        scalar start_;

        //- Duration of the damp function
        // scalar duration_;

        // threshold value; if exceeds, blending occurs (< 1)
        scalar thresholdValue_;

        // max. reference value; if exceeds, blending coeff. becomes zero
        scalar maxValue_;

        //- Simple linear damp function
        //  which form the basis of many more complex damp functions
        inline scalar linearDamp(const scalar t, const scalar val) const
        {
            // return max(min((t - start_)/duration_, 1), 0);

            // no damping if run-time is smaller than damping start-time
            if(t< start_)
            {
                return 1;
            }

            return
            (1 - min(
                    max(
                        (val - thresholdValue_)/(maxValue_ - thresholdValue_), 
                        0
                    ),
                    1
                )
            );
        }


private:

    // Private Member Functions

        //- Read the coefficients from the given dictionary
        void read(const dictionary& coeffs, const fvMesh& mesh);

        //- Disallow default bitwise assignment
        void operator=(const damp&);


public:

    // Constructors

        //- Construct from entry name and dictionary
        damp
        (
            const word& entryName,
            const dictionary& dict,
            const fvMesh& mesh
        );


    //- Destructor
    virtual ~damp();


    // Member Functions

        //- Return value for time t
        virtual scalar value(const scalar t) const = 0;

        //- Write in dictionary format
        virtual void writeData(Ostream& os) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Function1MeshTypes
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
